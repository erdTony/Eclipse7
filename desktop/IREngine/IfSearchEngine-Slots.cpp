#include "IfSearchEngine.h"

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QSize>
#include <QStringList>
#include <QTimer>

#include <EigenFace.h>
#include <EigenFaceGenerator.h>
#include <EigenFaceSearcher.h>
#include <EigenFaceParameters.h>
#include <EigenFaceTemplate.h>
#include <FaceBase.h>

#include <Eyes.h>
#include <FileWriteProfile.h>
#include <ImageCache.h>
#include <ImageMarker.h>
#include <ImageSource.h>
#include <InputHotdir.h>
#include <QQRect.h>
#include <Return.h>
#include <Setting.h>
#include <Settings.h>
#include <Resolver.h>
#include <HeightGrid.h>
#include <SkinMatcher.h>
#include <CharacteristicColor.h>
#include <ClothesMatchProperties.h>
#include <ClothesMatcher.h>

#include "DetectorResult.h"
#include "DetectorResultList.h"
#include "IfSearchApplication.h"
#include "IfSearchWindow.h"
#include "ObjdetEyes.h"
#include "ObjdetFrontal.h"
#include "ObjdetRawArguments.h"

void IfSearchEngine::pulse(void)
{
    qDebug() << Q_FUNC_INFO;

#ifdef BUILD_OBJDET_EVAL
    if (mInputFiles.isEmpty())
    {
        if (options().finishedQuit)
            QTimer::singleShot(10, qApp, SLOT(quit()));
        else if (options().loop)
            getInputFiles();
        else if (getInputFiles())
            QTimer::singleShot(options().sampleMsec, this, SLOT(pulse()));
        else if (options().waitingMsec)
            QTimer::singleShot(options().waitingMsec, this, SLOT(pulse()));
        return;
    }
    QFileInfo tInputFile = mInputFiles.takeFirst();
    processEval(tInputFile);
    QTimer::singleShot(options().sampleMsec, this, SLOT(pulse()));
}

int IfSearchEngine::getInputFiles()
{
    mInputDir.cd(app()->exeFileInfo().dir().absolutePath());
    if ( ! mInputDir.cd(options().inputDir.path()))
        qCritical() << "No input directory at:" << mInputDir.absolutePath();
    static const QStringList scNameFilter = QStringList() << "*.JPG" << "*.PNG";
    mInputFiles = mInputDir.entryInfoList(scNameFilter);
    if (mInputFiles.isEmpty())
        qCritical() << "No input files in:" << mInputDir.absolutePath();
    return mInputFiles.count();
}

void IfSearchEngine::processEval(const QFileInfo fi)
{
    qInfo() << Q_FUNC_INFO << fi.baseName();
    const QImage cRawImage(fi.filePath());
    mCurrentInputImage = createInputImage(cRawImage);
    if (mCurrentInputImage.isNull())
        qCritical() << "Image skipped:" << fi.absoluteFilePath()
                  << cRawImage.format();
    Q_ASSERT(mpFrontal);
    app()->win()->clearPixmaps();
    mpFrontal->clear();
    ObjdetRawArguments tRaw;
    tRaw.factor(1.100), tRaw.neighbors(3), tRaw.flags(0),
        tRaw.set(ObjdetRawArguments::ForceRaw),
        tRaw.minSize(QSize()), tRaw.maxSize(QSize()),
        tRaw.inputSize(mCurrentInputImage.size());
    mpFrontal->inputImage(mCurrentInputImage);
    mpFrontal->set(tRaw);
    if ( ! mpFrontal->processCascadeClassifier(true))
        qCritical() << "Facial ObjDet failed:" << fi.absoluteFilePath();
    mFaceResults = mpFrontal->resultList();
    QImage tMarkedImage = mpFrontal->markedImage(500);
    const QFileInfo tMarkedFI(mMarkedDir, fi.baseName() + ".png");
    if (tMarkedImage.save(tMarkedFI.absoluteFilePath()))
        qInfo() << tMarkedFI.absoluteFilePath() << tMarkedImage;
    QImage tDetectImage = mpFrontal->detectImage(500);
    const QFileInfo tDetectFI(mFrontalObjDetDir, fi.baseName() + ".png");
    if (tDetectImage.save(tDetectFI.absoluteFilePath()))
        qInfo() << tDetectFI.absoluteFilePath() << tDetectImage;
    app()->win()->clearFacePixmaps();
    app()->win()->setMarked(tMarkedImage);
    app()->win()->setDetect(tDetectImage);
    if (mFaceResults.count() == 0)
    {
        const QFileInfo tNoFaceFI(mNoFaceDir, fi.baseName() + ".png");
        if (tMarkedImage.save(tNoFaceFI.absoluteFilePath()))
            qInfo() << tNoFaceFI.absoluteFilePath() << tMarkedImage;
        app()->win()->clearFacePixmaps();
    }
    extractDetectedFaceImages(fi);
    for (int ix = 0; ix < mFaceResults.count(); ++ix)
        findEyes(ix);
    if (options().deleteAfter)
    {
        QFile tInputFile(fi.filePath());
        tInputFile.remove();
        qDebug() << fi.absoluteFilePath() << "removed";
    }

}

QImage IfSearchEngine::createInputImage(const QImage raw)
{
    QImage result;
    const QSize cInputSize(raw.width() & 0xFFF0, raw.height() & 0xFFF0);
    const QRect cInputRect(QPoint((raw.width() - cInputSize.width()) / 2,
                                  (raw.height() - cInputSize.height()) / 2),
                           cInputSize);
    result = raw.copy(cInputRect);
    switch (result.format())
    {
    case QImage::Format_Grayscale16:
    case QImage::Format_Indexed8:
        result.convertTo(QImage::Format_Grayscale8);
        // Q_FALLTHROUGH();
    case QImage::Format_Grayscale8: // As is Greyscale
        break;

    case QImage::Format_BGR888: // TODO others as needed
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        result.convertTo(QImage::Format_ARGB32);
        // Q_FALLTHROUGH();
    case QImage::Format_ARGB32: // As is Color
        break;

    case QImage::Format_Invalid:
    case QImage::Format_Mono:
    case QImage::Format_MonoLSB:
    default:
        qWarning() << "Unsupported input image format" << result.format();
        result = QImage();
    }
    return result;
}

QImage IfSearchEngine::createEyesImage(const QImage &ltImage, const QImage &rtImage,
                                       const DetectorResultList &ltResults,
                                       const DetectorResultList &rtResults)
{
    Q_ASSERT(ltImage.width() == 64);
    QImage result(QSize(128, 128), QImage::Format_ARGB32);
    QPainter tPainter;
    tPainter.begin(&result);
    drawEye(&tPainter, ltImage, ltResults);
    drawEye(&tPainter, rtImage, rtResults);
    tPainter.end();
    return result;
}

QImage IfSearchEngine::createNormImage()
{
    const QSize cNormImageSize(128, 128);
    QImage result(cNormImageSize, QImage::Format_ARGB32);
    result.fill(Qt::gray);
    const QImage cFrameImage = mCurrentInputImage.convertedTo(QImage::Format_ARGB32);
    const QPointF cLtEyePoint(cNormImageSize.width() / 4, cNormImageSize.height() / 4);
    const QPointF cRtEyePoint = cLtEyePoint + QPointF(cNormImageSize.width() / 2, 0);
    const QLineF cNormEyeLine(cLtEyePoint, cRtEyePoint);
    const QPointF cNormEyeCenter = cNormEyeLine.center();
    QPointF eyeCenter = (mCurrentEyeLine.p1() + mCurrentEyeLine.p2()) / 2;
    double fall = mCurrentEyeLine.p2().y() - mCurrentEyeLine.p1().y();
    double run  = qMax(1, mCurrentEyeLine.p2().x() - mCurrentEyeLine.p1().x());
    double theta = atan(fall / run);
    double eyeDistance = sqrt(fall * fall + run * run);
    double outDistance = cNormEyeLine.p2().x() - cNormEyeLine.p1().x();
    double scale = eyeDistance / outDistance;
    // T (top) point locates line above eyes
    QPointF T = eyeCenter + QPointF(scale * cNormEyeCenter.y() *  sin(theta),
                                    scale * cNormEyeCenter.y() * -cos(theta));
    // O (origin) is origin of normalized image
    QPointF O = T - QPointF(scale * cNormEyeCenter.x() * cos(theta),
                            scale * cNormEyeCenter.x() * sin(theta));

    double scaledSin = scale * sin(theta);
    double scaledCos = scale * cos(theta);
    for (int r = 0; r < cNormImageSize.height(); ++r)
    {
        for (int c = 0; c < cNormImageSize.width(); ++c)
        {
            double x = O.x() - (double)r * scaledSin + (double)c * scaledCos,
                y = O.y() + (double)r * scaledCos + (double)c * scaledSin;
            int ix = x + 0.5, iy = y + 0.5;
            if (ix >= 0 && ix < cFrameImage.width()
                && iy >= 0 && iy < cFrameImage.height())
            {
                const QRgb cFrameRgb = cFrameImage.pixel(ix, iy);
                result.setPixel(ix, iy, cFrameRgb);
            }
        } // for(c)
    } // for(r)

    return result;

}

void IfSearchEngine::drawEye(QPainter * pPainter, const QImage &eyeImage,
                               const DetectorResultList &eyeResults)
{
    pPainter->drawImage(QPoint( 0, 0), eyeImage);
    pPainter->drawImage(QPoint(64, 0), eyeImage.convertedTo(QImage::Format_Grayscale8));
    DetectorResult::List tResultRanked = eyeResults.rankedList();
    while ( ! tResultRanked.isEmpty())
    {
        const DetectorResult dr = tResultRanked.takeLast();
        const QRect cRect = dr.rect();
        //const int cQuality = dr.quality();
        const QColor cColor = dr.qualityColor(500);
        QPen tPen(QBrush(cColor), 3);
        pPainter->setPen(tPen);
        pPainter->drawRect(cRect);
    }
    pPainter->setPen(Qt::magenta);
    foreach (const QRect rc, eyeResults.allRectList())
        pPainter->drawRect(QRect(rc.topLeft() + QPoint(64, 0), rc.size()));

}

void IfSearchEngine::extractDetectedFaceImages(const QFileInfo &inputFI,
                                               const int minQuality)
{
    qInfo() << Q_FUNC_INFO << mFaceResults.count();
    app()->win()->clearFacePixmaps();
    foreach (const DetectorResult cResult, mFaceResults.rankedList())
    {
        const int cQuality = cResult.quality();
        if (cQuality < minQuality) break;               /*-----*/
        const QRect cDetectRect = cResult.rect();
        const QRect cCropRect = cDetectRect; // TODO?
        const int cRank = cResult.rank();
        const QImage cFaceImage = mCurrentInputImage.copy(cCropRect);
        mDetectedFaceImages.append(cFaceImage);
        const QString cFaceFileName
            = QString("./Q%1/#%2q%3x%4y%5w%6e%7-%8.png")
                  .arg(cQuality/100*100, 3, 10, QChar('0'))     // 1
                  .arg(cRank, 2, 10, QChar('0'))                // 2
                  .arg(cQuality, 3, 10, QChar('0'))             // 3
                  .arg(cDetectRect.x(), 4, 10, QChar('0'))      // 4
                  .arg(cDetectRect.y(), 4, 10, QChar('0'))      // 5
                  .arg(cDetectRect.width(), 3, 10,QChar('0'))   // 6
                  .arg(0, 3, 10, QChar('0'))                    // 7
                  .arg(inputFI.baseName());                     // 8
        const QFileInfo cFaceFI(mDetectedFacesDir, cFaceFileName);
        cFaceFI.dir().mkpath(".");
        qInfo() << cFaceFI.absoluteFilePath()
                << cFaceImage.save(cFaceFI.filePath(), "PNG", 90);
        const QImage cNormImage = createNormImage();
        app()->win()->appendFace(cFaceImage, mCurrentEyesImage, cNormImage);
    }

}

void IfSearchEngine::findEyes(const int faceIndex)
{
    qInfo() << Q_FUNC_INFO << faceIndex;
    const QImage cFaceImage = mDetectedFaceImages.at(faceIndex);
    const QSize cEyeImageSize(64,64);
    const QSize cCropSize = cFaceImage.size() / 2;
    const QImage cLtImage = cFaceImage.copy(QRect(QPoint(0, 0),
                                                  cCropSize)).scaled(cEyeImageSize);
    const QImage cRtImage = cFaceImage.copy(QRect(QPoint(cFaceImage.width() / 2, 0),
                                                  cCropSize)).scaled(cEyeImageSize);
    mpEyes->clear();
    ObjdetRawArguments tRaw;
    tRaw.factor(1.100), tRaw.neighbors(3), tRaw.flags(0),
        tRaw.set(ObjdetRawArguments::ForceRaw),
        tRaw.minSize(QSize()), tRaw.maxSize(QSize()),
        tRaw.inputSize(mCurrentInputImage.size());
    mpEyes->inputImage(cLtImage);
    mpEyes->set(tRaw);
    if ( ! mpEyes->processCascadeClassifier(true))
        qCritical() << "Left ObjDet failed:" << faceIndex;
    DetectorResultList tLtResultList = mpEyes->resultList();
    mpEyes->inputImage(cRtImage);
    if ( ! mpEyes->processCascadeClassifier(true))
        qCritical() << "Right ObjDet failed:" << faceIndex;
    DetectorResultList tRtResultList = mpEyes->resultList();
    mCurrentEyesImage = createEyesImage(cLtImage, cRtImage, tLtResultList, tRtResultList);
    const QRect cFaceRect = mFaceResults.at(faceIndex).rect();
    mCurrentEyeLine = QLine(cFaceRect.topLeft()
                    + tLtResultList.best().rect().center(),
                            cFaceRect.bottomRight()
                                + tRtResultList.best().rect().center());
}
#endif
#ifndef TODO0002
    //FUNCTION();
    //DETAIL("%1 grabs in cache", imageCache.grabSize());
    if (optShutdown->toBool())
    {
        QTimer::singleShot(10, this, SLOT(quit()));
        return;
    }

    if ( ! imageCache.isGrabEmpty())
        QTimer::singleShot(10, this, SLOT(processGrab()));

    if ( ! pendingFaces.isEmpty())
        QTimer::singleShot(10, this, SLOT(processFace()));

    imageCache.cleanAll();
    if (camera && imageCache.isGrabEmpty() && ! paused)
    {
        int rs = optRestartSecs->toInt();
        int sec = camera->msecsSinceLastGrab() / 1000;
        DETAIL("%1 seconds since last grab", sec);
        if (rs && sec >= rs)
        {
            WARNING("Restarting Camera");
            camera->restart();
        }
    }
    QTimer::singleShot(500, this, SLOT(pulse()));
} // pulse()
#endif

#ifndef TODO0002
void IfSearch::hotdirReady(void)
{
    FUNCTION();
    Q_ASSERT(hotdir);
    if ( ! paused)
    {
        hotdir->cacheFirst();
        QTimer::singleShot(10, this, SLOT(processGrab()));
    }
}

void IfSearch::hotdirEmpty(void)
{
    PROGRESS(">>>>>>Input HotDir Processing Complete");
#ifdef ENABLE_AVGFACE
    if (optAvgFaceEnable->toBool())
        avgFaceFinish();
#endif
}


void IfSearch::grabbed(QString ImageId)
{
    FUNCTION();
    QTimer::singleShot(10, this, SLOT(processGrab()));
} // grabbed()

void IfSearch::error(QString msg)
{
    ERRMSG(msg);
}

void IfSearch::warn(QString msg)
{
    WARNING(msg);
}

void IfSearch::error2(QString id, QString msg)
{
    ERRMSG("%1 error for %2", msg, id);
}

void IfSearch::logRollover(void)
{
    PROGRESS("Log Rollover initiated");
    Info::rollover();
    PROGRESS("Log Rollover complete");
    Info::flush();
}


void IfSearch::directorySet(QString profileName, QString absoluteDirName)
{
    DETAIL("%1 directory set to %2", profileName,
         absoluteDirName.isEmpty() ? "[None]" : absoluteDirName);
}

void IfSearch::fileWritten(QString absoluteFilePath)
{
    DETAIL("Wrote %1", absoluteFilePath);
}

void IfSearch::done(void)
{
    Info::flush();
    if (fpWriter)
        fpWriter->close();
    if ( ! optNoPrompt->toBool())
    {
        printf("\n===Press <ENTER> to exit...");
        getchar();
    }
    delete appSettings;
    QTimer::singleShot(0, qApp, SLOT(quit()));
} // done()

void IfSearch::changed(QString key)
{
    Q_ASSERT(appSettings);
    INFO(tr("PC=%3 %1 changed to %2", "status"), key,
         appSettings->valueOf(key), appSettings->pollCount());

    if (false)
        ;
    else if (0 == key.compare(optShutdown->keyName(), Qt::CaseInsensitive))
    {
        if (optShutdown->toBool())
        {
            QTimer::singleShot(100, qApp, SLOT(done()));
            return;
        }
    }
    else if (0 == key.compare(tr("Input/URL", "config"), Qt::CaseInsensitive))
    {
        appSettings->setValue("Output/FramesProcessed",
                              QString::number(FramesProcessed=0));
        appSettings->setValue("Output/NullFrames",
                              QString::number(NullFrames=0));
        appSettings->setValue("Output/FacesProcessed",
                              QString::number(FacesProcessed=0));
        if (camera)
            camera->stop();
        imageCache.flushGrab();
        if (camera)
        {
            delete camera;
            camera = 0;
        }
        if (hotdir)
        {
            hotdir->stop();
            delete hotdir;
            hotdir = 0;
        }
        appSettings->setValue("Input/NumFiles", "0");

        /*---- Setup Input Sources ----*/

        QUrl url(optInput->toString());
        if (url.isEmpty())
        {
            WARNING("Input/URL is empty");
            Info::flush();
        }
        else if ( ! url.isValid())
        {
            WARNING("Input/URL %1 is not valid", url.toString());
        }
        else if (0 == url.scheme().compare("dir", Qt::CaseInsensitive))
        {
            streamBase_mst.set(MillisecondTime::null());
            hotdir = new InputHotdir(this);
            Q_ASSERT(hotdir);
            hotdir->setObjectName("hotdir");
            hotdir->setCache(&imageCache);
            appSettings->objectProperties(hotdir, tr("Input", "config"),
                                          QStringList() << "SampleMsec" << "NewOnly"
                                          << "DeleteAfter" << "MoveAfter"
                                          << "BeginDateTime" << "EndDateTime"
                                          << "Skip" << "Jump" << "Loop" << "ImageId"
                                          << "MaxCache" << "OrderBy",
                                          Settings::Volatile);
            connect(hotdir, SIGNAL(ready()), this, SLOT(hotdirReady()));
            connect(hotdir, SIGNAL(empty()), this, SLOT(hotdirEmpty()));
            connect(hotdir, SIGNAL(grabCached(QString)), this, SLOT(grabbed(QString)));
            connect(hotdir, SIGNAL(grabError(QString)), this, SLOT(error(QString)));
            connect(hotdir, SIGNAL(grabWarn(QString)), this, SLOT(warn(QString)));

            QUrl url(optInput->toString());
            PROGRESS(tr("Starting %1", "progress message"), url);
            Info::flush();
            QString err = hotdir->start(url);
            if (err.isEmpty())
            {
                INFO(tr("File types supported: %1", "progress message"),
                     hotdir->filters().join(" "));
                INFO(tr("%1 files ready in %2", "progress message"),
                     hotdir->numPending(), hotdir->absolutePath());
                appSettings->setValue("Input/NumFiles",
                                      QString::number(hotdir->numPending()));
                changed(optPause->keyName());
                QTimer::singleShot(100, this, SLOT(pulse()));
            }
            else
                ERRMSG(tr("Error starting %2: %1", "error message"),
                      err, optInput->toString());
            Info::flush();
        }
        else if ("http" == url.scheme())
        {
            streamBase_mst.set(MillisecondTime::null());
            camera = new ImageSource(this);
            Q_ASSERT(camera);
            camera->setObjectName("source");
            camera->setCache(&imageCache);
            QStringList qsl;
            qsl << "SampleMsec" << "SourceId" << "BeginDateTime" << "EndDateTime";
            appSettings->objectProperties(camera, tr("Input", "config"), qsl, Settings::Volatile);
            qsl.clear();
            qsl << "MaxCache";
            appSettings->objectProperties(camera, tr("Input", "config"), qsl, Settings::Volatile | Settings::Advanced);
            connect(camera, SIGNAL(grabCached(QString)), this, SLOT(grabbed(QString)));
            connect(camera, SIGNAL(grabError(QString)), this, SLOT(error(QString)));
            connect(camera, SIGNAL(grabWarn(QString)), this, SLOT(warn(QString)));

            QString err = camera->selectNetcam(optInput->toString(),
                                               appSettings->value("Input/Format").toString());
            if ( ! err.isEmpty())
                ERRMSG(tr("Error starting %2: %1", "error message"), err, optInput->toString());
            else
            {
                camera->start();
                changed(optPause->keyName());
            }
        }
        else
        {
            WARNING("Unsupported Input/URL scheme: %1", url.scheme());
        }
        appSettings->dump(Info::Severity::Info, "Input/");
    }
    else if (0 == key.compare(optPause->keyName(), Qt::CaseInsensitive))
    {
        if (optPause->toBool())
        {
            if (camera)
                camera->setPaused(true);
            if (ffdBusy)
            {
                pausePending = true;
                PROGRESS("---PAUSE PENDING---");
            }
            else
            {
                imageCache.flushGrab();
                pendingFaces.clear();
                paused = true;
            }
        }
        else
        {
            if (camera)
                camera->setPaused(false);
            paused = false;
        }
    }
    else if (0 == key.compare(tr("Enroll/Command", "config"), Qt::CaseInsensitive))
    {
        if ( ! commandMode.isEmpty())
        {
            ERRMSG("[ENROLL] Command mode busy in %1=%2", commandMode,
                  appSettings->value(commandMode+"/Command").toString());
            appSettings->setValue("Enroll/Command", QString());
            return;
        }
        else
            commandMode = "Enroll";
        if (0 == optEnrollCommand->toString().compare("Enroll", Qt::CaseInsensitive))
        {
            enrollTimeout = 10;
            QTimer::singleShot(10, this, SLOT(doEnroll()));
        }
        else if (0 == optEnrollCommand->toString().compare("Reload", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doReload()));
        else if (0 == optEnrollCommand->toString().compare("Delete", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doDelete()));
        else if (0 == optEnrollCommand->toString().compare("RemoveAll", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doRemoveAll()));
        else if (0 == optEnrollCommand->toString().compare("Remove", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doRemove()));
        else if (0 == optEnrollCommand->toString().compare("Rename", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doRename()));
        else if (0 == optEnrollCommand->toString().compare("Manual", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doManual()));
        else if (0 == optEnrollCommand->toString().compare("Reenroll", Qt::CaseInsensitive))
            QTimer::singleShot(10, this, SLOT(doReenroll()));
        else
        {
            if ( ! optEnrollCommand->toString().isEmpty())
                ERRMSG("[ENROLL] Bad Command %1", optEnrollCommand->toString());
            commandMode.clear();
        }
    }
    else if (0 == key.compare(tr("Search/Command", "config"), Qt::CaseInsensitive))
    {
        if ( ! commandMode.isEmpty())
        {
            ERRMSG("[SEARCH] Command mode busy in %1=%2", commandMode,
                  appSettings->value(commandMode+"/Command").toString());
            appSettings->setValue("Search/Command", QString());
            return;
        }
        else
            commandMode = "Search";
        writer->pumpAll();
        if (0 == optSearchCommand->toString().compare("Search", Qt::CaseInsensitive))
        {
            searchTimeout = 10;
            QTimer::singleShot(10, this, SLOT(doSearch()));
        }
        else if (0 == optSearchCommand->toString().compare("Verify", Qt::CaseInsensitive))
        {
            searchTimeout = 10;
            QTimer::singleShot(10, this, SLOT(doVerify()));
        }
        else if (0 == optSearchCommand->toString().compare("Authenticate", Qt::CaseInsensitive))
        {
            searchTimeout = 10;
            QTimer::singleShot(10, this, SLOT(doAuthenticate()));
        }
        else if (0 == optSearchCommand->toString().compare("Similarity", Qt::CaseInsensitive))
        {
            searchTimeout = 10;
            QTimer::singleShot(10, this, SLOT(doSimilarity()));
        }
        else
        {
            if ( ! optSearchCommand->toString().isEmpty())
                ERRMSG("[SEARCH] Bad Command %1", optSearchCommand->toString());
            commandMode.clear();
        }
    }
    else if (0 == key.compare(optRetrieveCommand->keyName(), Qt::CaseInsensitive))
    {
        if ( ! commandMode.isEmpty())
        {
            ERRMSG("[RETRIEVE] Command mode busy in %1=%2", commandMode,
                  appSettings->value(commandMode+"/Command").toString());
            appSettings->setValue("Retrieve/Command", QString());
            return;
        }
        else
            commandMode = "Retrieve";
        writer->pumpAll();
        if (0 == optRetrieveCommand->toString().compare("Retrieve", Qt::CaseInsensitive))
        {
            QTimer::singleShot(10, this, SLOT(doRetrieve()));
        }
        else if (0 == optRetrieveCommand->toString().compare("RetrieveAll", Qt::CaseInsensitive))
        {
            QTimer::singleShot(10, this, SLOT(doRetrieveAll()));
        }
        else if (0 == optRetrieveCommand->toString().compare("Status", Qt::CaseInsensitive))
        {
            QTimer::singleShot(10, this, SLOT(doStatus()));
        }
        else if (0 == optRetrieveCommand->toString().compare("PersonReport", Qt::CaseInsensitive))
        {
            QTimer::singleShot(10, this, SLOT(doPersonReport()));
        }
        else
        {
            if ( ! optRetrieveCommand->toString().isEmpty())
                ERRMSG("[RETRIEVE] Bad Command %1", optRetrieveCommand->toString());
            commandMode.clear();
        }
    }
    else if (0 == key.compare(optResolveMin->keyName(), Qt::CaseInsensitive))
        ;
    else if (0 == key.compare(optResolveMax->keyName(), Qt::CaseInsensitive))
        ;
    else if (0 == key.startsWith("Resolve/"), Qt::CaseInsensitive)
    {
        Q_ASSERT(resolver);
        QString item = key.split("/").last();
        resolver->setWeight(item, appSettings->value(key).toInt());
    }
    else if (0 == key.compare(optHeightEnable->keyName(), Qt::CaseInsensitive)
            || 0 == key.compare("Height/GridFile", Qt::CaseInsensitive))
    {
        Q_ASSERT(heightGrid);
        if (optHeightEnable->toBool())
        {
            QImage heightImage = heightGrid->initializeGrid();
            if (fwpHeight->isActive() && ! heightImage.isNull())
                fwpHeight->write(heightImage, "HeightGrid");
        }
    }

} // changed()
#endif
