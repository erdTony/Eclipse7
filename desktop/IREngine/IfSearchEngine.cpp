#include "IfSearchEngine.h"
#include "version.h"

#include <QtDebug>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QSize>
#include <QTimer>

#include "IfSearchApplication.h"
#include "IfSearchWindow.h"
#include "ObjdetEyes.h"
#include "ObjdetFrontal.h"
#include "SCRect.h"

IfSearchEngine::IfSearchEngine(IfSearchApplication *parent)
    : QObject(parent)
    , mpApplication(parent)
{
    setObjectName("IfSearchEngine");
    QTimer::singleShot(100, this, SLOT(init()));
} // c'tor

IfSearchEngine::~IfSearchEngine()
{
}

void IfSearchEngine::init(void)
{
    qDebug() << Q_FUNC_INFO;
    mBaseTimestamp = QDateTime::currentDateTime();
    QTimer::singleShot(100, this, SLOT(start()));
}

void IfSearchEngine::start(void)
{
    startFrontal();
    startEyes();
    QTimer::singleShot(100, this, SLOT(run()));
}

void IfSearchEngine::startFrontal()
{
    const QString cFileName = options().frontalDetectorFI.absoluteFilePath();
    const unsigned cFrontalFactor = options().frontalFactor;
    qDebug() << Q_FUNC_INFO << cFileName << cFrontalFactor;
    if (mpFrontal)
    {
        mpFrontal->unloadDetector();
        mpFrontal->deleteLater();
    }
    mpFrontal = new ObjdetFrontal(this);
    Q_ASSERT(mpFrontal);
    mpFrontal->loadDetectorXml(cFileName);
    if ( ! mpFrontal->isDetectorLoaded())
        qCritical() << "Failed to load frontal:" << mpFrontal->detectorFileInfo();
    ObjdetRawArguments tRaw;
    tRaw.setFactor(cFrontalFactor), tRaw.neighbors(1),
        tRaw.flags(0), tRaw.set(ObjdetRawArguments::ForceRaw),
        tRaw.minSize(48), tRaw.maxSize(0);
    mpFrontal->set(tRaw);
    foreach (const QString cs, mpFrontal->info()) qDebug() << cs;
}

void IfSearchEngine::startEyes()
{
    qDebug() << Q_FUNC_INFO << options().frontalDetectorFI.absoluteFilePath();
    if (mpLEyes)
    {
        mpLEyes->unloadDetector();
        mpLEyes->deleteLater();
    }
    if (mpREyes)
    {
        mpREyes->unloadDetector();
        mpREyes->deleteLater();
    }
    mpLEyes = new ObjdetEyes(Objdet::EyeLeft, this);
    mpLEyes->loadDetectorXml("./detectors/haarcascade_eye.xml");
    if ( ! mpLEyes->isDetectorLoaded())
        qCritical() << "Failed to load left eyes:" << mpLEyes->detectorFileInfo();
    mpREyes = new ObjdetEyes(Objdet::EyeRight, this);
    mpREyes->loadDetectorXml("./detectors/haarcascade_eye.xml");
    if ( ! mpREyes->isDetectorLoaded())
        qCritical() << "Failed to load right eyes:" << mpREyes->detectorFileInfo();
    ObjdetRawArguments tRaw;
    tRaw.setFactor(1.1), tRaw.neighbors(1), tRaw.flags(0),
        tRaw.set(ObjdetRawArguments::ForceRaw),
        tRaw.set(ObjdetRawArguments::Biggest),
        tRaw.minSize(QSize()), tRaw.maxSize(QSize());
    mpLEyes->set(tRaw);
    mpREyes->set(tRaw);
    foreach (const QString cs, mpLEyes->info()) qDebug() << cs;
}

void IfSearchEngine::run(void)
{
    qDebug() << Q_FUNC_INFO;

    scanInputDirectory();

    mOutputBaseDir.cd(app()->exeFileInfo().dir().absolutePath());
    QString tOutputBaseDirName = options().baseOutputDir.path();
    tOutputBaseDirName.replace('@', QDateTime::currentDateTime()
                                        .toString("DyyyyMMdd-Thhmm"));
    mOutputBaseDir.mkpath(tOutputBaseDirName);
    if ( ! mOutputBaseDir.cd(tOutputBaseDirName))
        qCritical() << "Can't set base output directory";
    mMarkedDir = mNoFaceDir = mFrontalObjdetDir = mEyesObjdetDir
        = mDetectedFacesDir = mOutputBaseDir;
    qDebug() << mOutputBaseDir << mMarkedDir << mDetectedFacesDir;
    if ( ! mMarkedDir.mkpath(options().markedDir.path()))
        qCritical() << "Can't make marked output directory";
    if ( ! mNoFaceDir.mkpath(options().noFaceDir.path()))
        qCritical() << "Can't make no faces detected output directory";
    if ( ! mDetectedFacesDir.mkpath(options().detectedFacesDir.path()))
        qCritical() << "Can't make detected faces output directory";
    if ( ! mFrontalObjdetDir.mkpath(options().frontalObjdetDir.path()))
        qCritical() << "Can't make frontal objdet output directory";
    if ( ! mEyesObjdetDir.mkpath(options().eyesObjdetDir.path()))
        qCritical() << "Can't make eyes objdet output directory";
    qDebug() << mOutputBaseDir << mMarkedDir << mDetectedFacesDir;
    if ( ! mMarkedDir.cd(options().markedDir.path()))
        qCritical() << "Can't set marked output directory";
    if ( ! mNoFaceDir.cd(options().noFaceDir.path()))
        qCritical() << "Can't set no faces detected output directory";
    if ( ! mDetectedFacesDir.cd(options().detectedFacesDir.path()))
        qCritical() << "Can't set detected faces output directory";
    if ( ! mFrontalObjdetDir.cd(options().frontalObjdetDir.path()))
        qCritical() << "Can't set objdet output directory";
    if ( ! mEyesObjdetDir.cd(options().eyesObjdetDir.path()))
        qCritical() << "Can't set objdet output directory";
    qDebug() << mOutputBaseDir << mMarkedDir << mDetectedFacesDir;
    Q_CHECK_PTR(mpFrontal);
    Q_ASSERT(mpFrontal->writeInfo(mFrontalObjdetDir)); // TODO WEXPECT

    QTimer::singleShot(1000, this, SLOT(pulse()));
} // run()


void IfSearchEngine::pulse(void)
{
    qDebug() << Q_FUNC_INFO;

    if (mInputFileList.isEmpty())
    {
        if (options().finishedQuit)
            QTimer::singleShot(100, qApp, SLOT(quit()));
        else if (options().loop)
        {
            if (scanInputDirectory())
                QTimer::singleShot(options().sampleMsec, this, SLOT(pulse()));
        }
        else if (options().waitingMsec)
            QTimer::singleShot(options().waitingMsec, this, SLOT(pulse()));
        return;
    }
    app()->win()->clearPixmaps();
    app()->win()->clearFaces();
    const QFileInfo cInputFile = mInputFileList.takeFirst();
    processFrame(cInputFile);
    QTimer::singleShot(options().sampleMsec, this, SLOT(pulse()));
}

void IfSearchEngine::processFrame(const QFileInfo &fi)

{
    qInfo() << Q_FUNC_INFO << fi.baseName();
    const QImage cInputImage = readInputImage(fi);
    if (cInputImage.isNull())
        qCritical() << "Image skipped:" << fi.absoluteFilePath();
    Q_ASSERT(mpFrontal);
    Q_ASSERT(mpFrontal->isDetectorLoaded());
    mpFrontal->clear();
    mpFrontal->inputImage(cInputImage);
    if ( ! mpFrontal->processCascadeClassifier(true))
        qCritical() << "ObjDet failed:" << fi.absoluteFilePath();
    mCurrentFrameFI = fi;
    mCurrentFrameImage = cInputImage;
    mFrameFaceDRL = mpFrontal->resultList();

    processFaces();
    writeFrameImages();
    if (options().deleteAfter)
    {
        QFile tInputFile(fi.filePath());
        tInputFile.remove();
        qDebug() << fi.absoluteFilePath() << "removed";
    }

}

void IfSearchEngine::processFaces()
{
    const unsigned cMinQuality = options().minQuality;
    qInfo() << Q_FUNC_INFO << mFrameFaceDRL.count() << cMinQuality;
    app()->win()->clearFaces();
    foreach (const DetectorResult cFaceDR, mFrameFaceDRL.rankedList())
    {
        mCurrentFaceDR = cFaceDR;
        const unsigned cQuality = cFaceDR.quality();
        if (cQuality >= cMinQuality)
        {
            calculateFaceRect();
            extractFaceImage();
            writeFaceImage();
            app()->win()->appendFace(mCurrentFaceImage.scaled(IfSearchWindow::faceThumbSize()));
#ifndef NOEYEFIND
            calculateEyeRoi(Objdet::EyeLeft);
            const DetectorResultList cLtEyeDRL = findEyeDRL(Objdet::EyeLeft);
            const DetectorResultList cRtEyeDRL = findEyeDRL(Objdet::EyeRight);
            selectBestEyes(cLtEyeDRL, cRtEyeDRL);
#endif
        }
    }
}

int IfSearchEngine::scanInputDirectory()
{
    mInputDir.cd(app()->exeFileInfo().dir().absolutePath());
    if ( ! mInputDir.cd(options().inputDir.path()))
        qCritical() << "No input directory at:" << mInputDir.absolutePath();
    static const QStringList scNameFilter = QStringList() << "*.JPG" << "*.PNG";
    mInputFileList = mInputDir.entryInfoList(scNameFilter);
    if (mInputFileList.isEmpty())
        qCritical() << "No input files in:" << mInputDir.absolutePath();
    return mInputFileList.isEmpty();
}

QImage IfSearchEngine::readInputImage(const QFileInfo &fi)
{
    QImage result;
    const QImage cInputImage(fi.filePath());
    SCRect tInputRect(cInputImage.rect());
    tInputRect.trim(16);
    result = QImage(cInputImage).copy(tInputRect);
    if (result.isNull())
        qWarning() << "Null input image" << fi.absoluteFilePath();
    return result;
}

void IfSearchEngine::writeFrameImages()
{
    const QString cFileName = mCurrentFrameFI.baseName() + ".png";
    const unsigned cMinQuality = options().minQuality;
    mCurrentDetectImage = mpFrontal->detectImage(cMinQuality);
    const QFileInfo tDetectFI(mFrontalObjdetDir, cFileName);
    if (mCurrentDetectImage.save(tDetectFI.absoluteFilePath()))
        qInfo() << tDetectFI.absoluteFilePath() << mCurrentDetectImage.size();
    app()->win()->setDetect(mCurrentDetectImage);

    Q_CHECK_PTR(mpLEyes); Q_CHECK_PTR(mpREyes);
    mCurrentMarkedImage = mpFrontal->markedImage(mpLEyes->eyeRect(),
                                                 mpREyes->eyeRect(), cMinQuality);
    const QFileInfo tMarkedFI(mMarkedDir, cFileName);
    if (mCurrentMarkedImage.save(tMarkedFI.absoluteFilePath()))
        qInfo() << tMarkedFI.absoluteFilePath() << mCurrentMarkedImage.size();
    app()->win()->setMarked(mCurrentMarkedImage);
    if (mFrameFaceDRL.count(cMinQuality) == 0)
    {
        const QFileInfo tNoFaceFI(mNoFaceDir, cFileName);
        if (mCurrentMarkedImage.save(tNoFaceFI.absoluteFilePath()))
            qInfo() << tNoFaceFI.absoluteFilePath() << mCurrentMarkedImage.size();
    }
}

SCRect IfSearchEngine::calculateFaceRect()
{
    const SCRect cDetectRect = mCurrentFaceDR.rect();
    SCRect result = (cDetectRect * (qreal(options().faceOverCrop) / 100.0)).trimmed(16);
    qInfo() << Q_FUNC_INFO
            << mCurrentFaceDR.rect().toDebugString()
            << result.toDebugString();
    return mCurrentFaceRect = result;
}

QImage IfSearchEngine::extractFaceImage()
{
    const QImage result = mCurrentFrameImage.copy(mCurrentFaceRect);
    qInfo() << Q_FUNC_INFO << mCurrentFaceRect.toDebugString() << result.size();
    return mCurrentFaceImage = result;
}

bool IfSearchEngine::writeFaceImage()
{
    const int cRank = mCurrentFaceDR.rank();
    const int cQuality = mCurrentFaceDR.quality();
    const QString cFaceFileName
        = QString("./Q%1/#%2q%3x%4y%5w%6e%7-%8.png")
              .arg(cQuality/100*100, 3, 10, QChar('0'))     // 1
              .arg(cRank, 2, 10, QChar('0'))                // 2
              .arg(cQuality, 3, 10, QChar('0'))             // 3
              .arg(mCurrentFaceRect.x(), 4, 10, QChar('0'))      // 4
              .arg(mCurrentFaceRect.y(), 4, 10, QChar('0'))      // 5
              .arg(mCurrentFaceRect.width(), 3, 10,QChar('0'))   // 6
              .arg(0, 3, 10, QChar('0'))                    // 7
              .arg(mCurrentFrameFI.baseName());                     // 8
    const QFileInfo cFaceFI(mDetectedFacesDir, cFaceFileName);
    cFaceFI.dir().mkpath(".");
    const bool result = mCurrentFaceImage.save(cFaceFI.filePath(), "PNG", 90);
    qInfo() << Q_FUNC_INFO << cFaceFI.absoluteFilePath()
            << mCurrentFaceImage.size() << result;
    return result;
}
/*
QImage IfSearchEngine::writeFaceImage(const QFileInfo inputFI,
                                      const QImage &inputImage,
                                      const DetectorResult faceResult)
{
    const int cRank = faceResult.rank();
    const int cQuality = faceResult.quality();
    const QString cFaceFileName
        = QString("./Q%1/#%2q%3x%4y%5w%6e%7-%8.png")
              .arg(cQuality/100*100, 3, 10, QChar('0'))     // 1
              .arg(cRank, 2, 10, QChar('0'))                // 2
              .arg(cQuality, 3, 10, QChar('0'))             // 3
              .arg(mCurrentFaceRect.x(), 4, 10, QChar('0'))      // 4
              .arg(mCurrentFaceRect.y(), 4, 10, QChar('0'))      // 5
              .arg(mCurrentFaceRect.width(), 3, 10,QChar('0'))   // 6
              .arg(0, 3, 10, QChar('0'))                    // 7
              .arg(inputFI.baseName());                     // 8
    const QFileInfo cFaceFI(mDetectedFacesDir, cFaceFileName);
    cFaceFI.dir().mkpath(".");
    qInfo() << cFaceFI.absoluteFilePath()
            << cFaceImage.save(cFaceFI.filePath(), "PNG", 90);
    app()->win()->appendFace(cFaceImage.scaled(IfSearchWindow::faceThumbSize()));
    return cFaceImage;
}
*/
/*
void IfSearchEngine::findEyeDRL(const QImage &frameImage,
                              const QFileInfo inputFI,
                              const DetectorResult faceResult)
{
    Q_CHECK_PTR(mpLEyes); Q_CHECK_PTR(mpREyes);
    SCRect tLRoi = mpLEyes->calculateEyeRoi();
    SCRect tRRoi = mpREyes->calculateEyeRoi();
    QImage tLEyeImage = frameImage.copy(tLRoi.toQRect());
    QImage tREyeImage = frameImage.copy(tRRoi.toQRect());
    int tLEyeScale = (tLEyeImage.width() >= 96) ? 1
                         : qRound(96 / tLEyeImage.width() + 0.999);
    int tREyeScale = (tREyeImage.width() >= 96) ? 1
                         : qRound(96 / tREyeImage.width() + 0.999);
    tLEyeImage = tLEyeImage.scaledToWidth(tLEyeImage.width() * tLEyeScale);
    tREyeImage = tREyeImage.scaledToWidth(tREyeImage.width() * tREyeScale);
    const DetectorResultList cLEyeResults
        = findEye(Objdet::EyeLeft,  tLEyeImage, tLRoi, tLEyeScale);
    const DetectorResultList cREyeResults
        = findEye(Objdet::EyeRight, tREyeImage, tRRoi, tREyeScale);
    mCurrentFaceLEyeDRL = cLEyeResults;
    mCurrentFaceREyeDRL = cREyeResults;
    const QImage cLEyeImage
        = writeEyeImage(false, inputFI, tLEyeImage, faceResult, cLEyeResults);
    const QImage cREyeImage
        = writeEyeImage(true,  inputFI, tREyeImage, faceResult, cREyeResults);
    app()->win()->appendEyes(cLEyeImage, cREyeImage);
}
*/
DetectorResultList IfSearchEngine::findEyeDRL(const Objdet::Class objcls)
{
    DetectorResultList result;
    ObjdetEyes * pEyeObjdet = new ObjdetEyes(objcls,
                                            mCurrentFrameImage,
                                            mCurrentFaceDR, this);
    const QImage * pImage = (Objdet::EyeLeft == objcls)
                                ? &mLtEyeRoiImage
                                : &mRtEyeRoiImage;
    const SCRect cEyeRect = pEyeObjdet->eyeRect();
    pEyeObjdet->inputImage(*pImage, cEyeRect);
    pEyeObjdet->calculateEyeRoi();

    // TODO detect

    qInfo() << Q_FUNC_INFO << objcls << cEyeRect << result.toDebugStrings();
    return result;
}

SCLine IfSearchEngine::selectBestEyes(const DetectorResultList ltDRL,
                                      const DetectorResultList rtDRL)
{
    SCLine result;
    mCurrentFaceLEyeDR = mCurrentFaceREyeDR = DetectorResult();
    if ( ! ltDRL.isEmpty() &&  ! rtDRL.isEmpty())
    { // TODO Smarter
        mCurrentFaceLEyeDR = ltDRL.best();
        mCurrentFaceREyeDR = rtDRL.best();
        result.lt(mCurrentFaceLEyeDR.rect());
        result.rt(mCurrentFaceLEyeDR.rect());
    }
    result = result.offsetBy(mCurrentFaceRect.center());
    return mCurrentFrameEyeLine = result;
}

SCRect IfSearchEngine::calculateEyeRoi(const Objdet::Class objcls)
{
    ObjdetEyes * pODE = eyeObjdet(objcls);
    SCRect result = pODE->eyeRect();
    result.trim(16);
    qInfo() << Q_FUNC_INFO << objcls << result.toDebugString();
    return result;
}

void IfSearchEngine::extractEyeImages()
{
    mLtEyeRoiImage = mCurrentFrameImage.copy(mCurrentFrameEyeLine.lt());
    mRtEyeRoiImage = mCurrentFrameImage.copy(mCurrentFrameEyeLine.rt());
}
/*
DetectorResultList IfSearchEngine::findEye(const Objdet::Class objClass,
                                            const QImage &eyeImage,
                                            const SCRect eyeRoi,
                                            const int eyeScale)
{
    qInfo() << Q_FUNC_INFO << objClass << eyeRoi << eyeScale;
    DetectorResultList result;
    ObjdetEyes * pEyes = eyeObjdet(objClass);
    Q_ASSERT(pEyes->isDetectorLoaded());
    pEyes->inputImage(eyeImage);
    if ( ! pEyes->processCascadeClassifier(true))
        qCritical() << "ObjDet eyes failed";
    result = pEyes->resultList();
    result.adjustRanked(eyeRoi, eyeScale);
    return result;
}
*/
ObjdetEyes *IfSearchEngine::eyeObjdet(const Objdet::Class objcls)
{
    ObjdetEyes * result = (Objdet::EyeLeft == objcls) ? mpLEyes : mpREyes;
    Q_CHECK_PTR(result);
    return result;
}


/*
QImage IfSearchEngine::writeEyeImage(const bool isRight,
                                     const QFileInfo inputFI,
                                     const QImage eyeImage,
                                     const DetectorResult faceDR,
                                     const DetectorResultList eyeDRL)
{
    static const int scThumbWidth = IfSearchWindow::faceThumbSize().width();
    QImage result = eyeImage.scaledToWidth(scThumbWidth / 2);
    const qreal cScaleF = qreal(scThumbWidth) / qreal(eyeImage.width());
    qInfo() << Q_FUNC_INFO << isRight << inputFI.baseName() << eyeImage.size()
            << faceDR.toDebugStrings()
            << (eyeDRL.isEmpty()
                    ? (QStringList() << "eye results empty")
                    : eyeDRL.best().toDebugStrings());
    QPainter tPainter;
    tPainter.begin(&result);
    foreach (const DetectorResult cDR, eyeDRL.rankedList())
    {
        const SCRect cRect = cDR.rect();
        QPen tPen(cDR.eyeQualityColor());
        tPainter.setPen(tPen);
        tPainter.drawRect((cRect * cScaleF).toQRect());
    }
    tPainter.end();
    const QString cEyeFileName
        = QString("./#%1%2eye-%3.png")
              .arg(faceDR.rank(), 2, 10, QChar('0'))                // 1
              .arg(isRight ? "R" : "L")                             // 2
              .arg(inputFI.baseName());                             // 3
    const QFileInfo cEyeFI(mEyesObjdetDir, cEyeFileName);
    qInfo() << cEyeFI.absoluteFilePath()
            << result.save(cEyeFI.filePath(), "png", 90);
    return result;
}
*/
