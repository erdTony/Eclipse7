#include "Objdet.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>

#include <opencv2/opencv.hpp>

#include <ObjectHelper.h>
#include "ObjdetRawArguments.h"

Objdet::Objdet(QObject *parent)
    : QObject{parent}
    , cmClass($nullClass)
{
    setObjectName("Objdet:Null");
}

Objdet::~Objdet()
{
    if (mpCascade) delete mpCascade;
}

Objdet::Objdet(const Class objcls, QObject *parent)
    : QObject{parent}
    , cmClass(objcls)
    , mpCascade(new cv::CascadeClassifier())
{
    setObjectName("Objdet:" + QString::number(objcls));
}

void Objdet::loadDetectorXml(const QString &fileName)
{
    qDebug() << Q_FUNC_INFO << fileName;
    unloadDetector();
    QFileInfo tFI(fileName);
    if ( ! tFI.isReadable())
    {
        QString tErrMsg("File not readable:" + tFI.absoluteFilePath());
        emit error(tErrMsg);
        qCritical() << tErrMsg;
    }
    std::basic_string<char,
                           std::char_traits<char>,
                           std::allocator<char> > const&
        cStdCascadeXmlName = tFI.absoluteFilePath().toStdString();

    Q_ASSERT(mpCascade);
    if ( ! mpCascade->load(cStdCascadeXmlName))
    {
        QString tErrMsg("File failed to load:" + tFI.absoluteFilePath());
        emit error(tErrMsg);
        qCritical() << tErrMsg;
        unloadDetector();
    }
    mCascadeFileInfo = tFI;
    Q_ASSERT( ! mpCascade->empty());
}

void Objdet::unloadDetector()
{
    Q_ASSERT(mpCascade);
    if (isDetectorLoaded())
        mpCascade->load("");
    mCascadeFileInfo = QFileInfo();
    Q_ASSERT(mpCascade->empty());
}

QStringList Objdet::info() const
{
    QStringList result;
    result << "Object Detector Information:";
    result << QString("   Class: %1").arg(className());
    result << QString("   Name: %1").arg(detectorFileInfo().baseName());
    // TODO ObjdetParameters
    result << "---Raw Arguments:";
    result << raw().toStrings();
    return result;
}

bool Objdet::writeInfo(const QDir &dir) const
{
    QFileInfo tFI(dir, className() + "ObjDetInfo.txt");
    QFile tFile(tFI.filePath());
    if ( ! tFile.open(QIODevice::Text | QIODevice::WriteOnly)) return false;
    foreach (const QString cQS, info())
        tFile.write(qPrintable(cQS + "\n"));
    tFile.close();
    return true;
}



void Objdet::set(const ObjdetRawArguments raw)
{
    qDebug() << Q_FUNC_INFO << raw.factor() << raw.neighbors()
             << raw.flags() << raw.minSize() << raw.minSize()
             << raw.inputSize();
    mRawArgs = raw;
}

void Objdet::inputImage(const QImage &img)
{
    qInfo() << Q_FUNC_INFO << img.size();
    mInputImage = img.convertedTo(QImage::Format_ARGB32);
    mGreyImage = inputImage().convertedTo(QImage::Format_Grayscale8);
    mGreyMat = cv::Mat(mGreyImage.height(),
                       mGreyImage.width(), CV_8U);
    const int cGreyMatBytes = mGreyMat.total();
    qDebug() << mGreyImage.size()
             << mGreyImage.sizeInBytes() << cGreyMatBytes;
    Q_ASSERT(mGreyImage.sizeInBytes() == cGreyMatBytes);
    memcpy(mGreyMat.ptr(0), mGreyImage.bits(), cGreyMatBytes);
    raw().inputSize(mInputImage.size());
}

void Objdet::inputImage(const QImage &img, const QRect rc)
{
    qInfo() << Q_FUNC_INFO << img.size() << rc;
    inputImage(img.copy(rc));
}

void Objdet::clear()
{
    mAllRects.clear(), mOrphanRects.clear(),
        mResultList.clearResults();
    inputImage(QImage());
    mGreyMat.deallocate();
    mGreyMat = cv::Mat();
}

bool Objdet::processCascadeClassifier(const bool returnAll)
{
    qInfo() << Q_FUNC_INFO << returnAll << inputImage().size();
    foreach (const QString cs, info()) qDebug() << cs;
    bool result = false;
    if ( ! isDetectorLoaded())
        return result;                                  /*=====*/
    if (inputImage().isNull())
        return result;                                  /*=====*/
    std::vector<cv::Rect> tRectVector;
    std::vector<int> tCountVector;
    std::vector<cv::Rect> tAllRectVector;
    Q_ASSERT(mpCascade);
    mpCascade->detectMultiScale(mGreyMat, tRectVector, tCountVector,
                                raw().factor(), raw().neighbors(), raw().flags(),
                                raw().cvMinSize(), raw().cvMaxSize());
    if (returnAll)
        mpCascade->detectMultiScale(mGreyMat, tAllRectVector,
                                    raw().factor(), 0, raw().flags(),
                                    raw().cvMinSize(), raw().cvMaxSize());

    result = processResults(tRectVector, tCountVector,
                            tAllRectVector, raw().factor());
    qDebug() << __LINE__ << tRectVector.size()
             << tCountVector.size() << tAllRectVector.size()
             << mOrphanRects.count();
    return result;
}

bool Objdet::processResults(const std::vector<cv::Rect> rects,
                            const std::vector<int> counts,
                            const std::vector<cv::Rect> allrects,
                            const qreal factor)
{
    for (unsigned ix = 0; ix < allrects.size(); ++ix)
    {
        const cv::Rect cCvRect = allrects.at(ix);
        const QRect cRect(cCvRect.tl().x, cCvRect.tl().y,
                          cCvRect.width, cCvRect.height);
        mAllRects.append(cRect);
    }
    QList<SCRect> tRectList = mAllRects;
    QMultiMap<int, DetectorResult> tQualityResultMap;
    for (unsigned ix = 0; ix < rects.size(); ++ix)
    {
        const cv::Rect cCvRect = rects.at(ix);
        const int cCount = counts.at(ix);
        const QRect cResultRect(cCvRect.tl().x, cCvRect.tl().y,
                                cCvRect.width, cCvRect.height);
        const int cQuality
            = calculateQuality(cCount, cResultRect.width(), factor);
        DetectorResult tResult(cResultRect);
        tResult.quality(cQuality);
        tResult.count(cCount);
        tRectList = tResult.takeIncludedRects(tRectList);
        tQualityResultMap.insert( - cQuality, tResult);
        qDebug() << Q_FUNC_INFO << cQuality << cResultRect
                 << tQualityResultMap.count() << tRectList.count();
    }
    mOrphanRects = tRectList;
    mResultList.orphanList(mOrphanRects);
    int tRank = 0;
    foreach (DetectorResult dr, tQualityResultMap.values())
    {
        dr.rank(++tRank);
        mResultList.addRanked(dr);
    }
    qDebug() << Q_FUNC_INFO << cmClass << mAllRects.count()
             << mOrphanRects.count()
             << mResultList.rankedList().count();
    return true;
}

int Objdet::calculateQuality(const int neighborCount,
                             const int detectWidth,
                             const qreal factor)
{
    int result = 0;
    Q_ASSERT(detectWidth);
    if ( ! qFuzzyCompare(1.100, mRawArgs.factor()))
        qWarning() << "Expected factor 1.100";
    result = int((qreal(neighborCount) / qreal(detectWidth))
                 * 500.0 * factor * factor);
    result = qBound(1, result, 999);
    //qDebug() << Q_FUNC_INFO << neighborCount << detectWidth << result;
    return result;
}

// -------------------------- static ------------------------

VersionInfo Objdet::cvVersion()
{
    VersionInfo ver(CV_MAJOR_VERSION,
                    CV_MINOR_VERSION,
                    CV_SUBMINOR_VERSION,
                    0, 0, "",
/*                    CV_VERSION,
                    "Copyright (c) 2000-2008, Intel Corporation. "
                    "Copyright (C) 2015-2024, OpenCV Foundation, all rights reserved."
                    "Thank you to huihut.com for prebuilt MINGW libraries.", */
                    "OpenCV",
                    "OpenCV Foundation",
                    "Computer Vision Library");
    ver.legal("Copyright (c) 2000-2008, Intel Corporation. "
              "Copyright (C) 2015-2024, OpenCV Foundation, "
              "all rights reserved.");
    return ver;
}

bool Objdet::isValid(const Class objcls)
{
    return objcls > $nullClass && objcls < $maxClass;
}

Objdet::Class Objdet::objectClass(const QString name)
{
    Objdet tOD;
    ObjectHelper tOH((QObject *)(&tOD));
    return Objdet::Class(tOH.enumValue("Class", name));
}

QString Objdet::className(const Objdet::Class objcls)
{
    Objdet tOD;
    ObjectHelper tOH((QObject *)(&tOD));
    return tOH.enumKey("Class", objcls);
}
