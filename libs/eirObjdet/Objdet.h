#pragma once

#include <QObject>

#include <QFileInfo>
#include <QImage>
#include <QList>
#include <QSize>
#include <QString>
#include <QStringList>


#include "DetectorResult.h"
#include "DetectorResultList.h"
#include "ObjdetParameters.h"
#include "ObjdetRawArguments.h"
#include <SCRect.h>
#include <VersionInfo.h>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>

class Objdet : public QObject
{
    Q_OBJECT
public: // types
    enum Class
    {
        $nullClass = 0,
        FaceFrontal,
        FaceProfileLeft,
        FaceProfileRight,
        Eyes,
        EyeLeft,
        EyeRight,
        EyeBoth,
        $maxClass
    };
    Q_ENUM(Class)
    typedef QList<Class> ClassList;

public: // ctors
    explicit Objdet(QObject *parent = nullptr);
    ~Objdet();
protected:  // ctors
    Objdet(const Class objcls, QObject * parent=0);

public slots:
    void loadDetectorName(const QString & name) { Q_UNUSED(name); } // TODO
    void loadDetectorXml(const QString & fileName);
    void unloadDetector();

signals:
    void selected(const QFileInfo &fi);
    void error(QString message);

protected:

public: // const
    Class objClass() const;
    QString className() const;
    QStringList info() const;
    bool writeInfo(const QDir &dir) const;
    ObjdetParameters parms() const;
    ObjdetRawArguments raw() const;
    QImage inputImage(void) const;
    QString performanceString(void) const;
    DetectorResultList resultList(void) const;
    QList<SCRect> allRects(void) const;
    QList<QSize> detectorSizes(void) const;
    bool isDetectorLoaded(void);
    QFileInfo detectorFileInfo() const;
    QSize sizeFromDetectorXml(const QString & fileName);
    QSize minObjectSize(void) const;
    QSize maxObjectSize(void) const;

public: // non-const
    void set(const ObjdetRawArguments raw);
    void inputImage(const QImage &img);
    void inputImage(const QImage &img, const QRect rc);
    void clear();
    bool processCascadeClassifier(const bool returnAll=false);

public: // pointers
    ObjdetRawArguments & raw();
    void cascade(cv::CascadeClassifier * pc);
    cv::CascadeClassifier * cascade(void);

public: // static
    static VersionInfo cvVersion();
    static bool isValid(const Objdet::Class objcls);
    static Objdet::Class objectClass(const QString name);
    static QString className(const Objdet::Class objcls);

public:

protected slots:

protected:
    const Class cmClass=$nullClass;

private:
    bool processResults(const std::vector<cv::Rect> rects,
                        const std::vector<int> counts,
                        const std::vector<cv::Rect> allrects, const qreal factor);
    int calculateQuality(const int neighborCount,
                         const int detectWidth,
                         const qreal factor);
    bool loadXmlCascade(const QString & xmlFilename);

private:
    QList<SCRect> mAllRects;
    QList<SCRect> mOrphanRects;
    DetectorResultList mResultList;
    QFileInfo mCascadeFileInfo;
    cv::CascadeClassifier * mpCascade=nullptr;
    ObjdetParameters mParms;
    ObjdetRawArguments mRawArgs;
    QImage mInputImage;
    QImage mGreyImage;
    cv::Mat mGreyMat;
};

inline Objdet::Class Objdet::objClass() const { return cmClass; }
inline QString Objdet::className() const { return  Objdet::className(objClass()); }
inline ObjdetRawArguments Objdet::raw() const { return mRawArgs; }
inline QImage Objdet::inputImage() const { return mInputImage; }
inline DetectorResultList Objdet::resultList() const { return mResultList; }
inline QList<SCRect> Objdet::allRects() const { return mAllRects; }
inline bool Objdet::isDetectorLoaded() { return ! cascade()->empty(); }
inline QFileInfo Objdet::detectorFileInfo() const { return mCascadeFileInfo; }
inline ObjdetRawArguments &Objdet::raw() { return mRawArgs; }
inline void Objdet::cascade(cv::CascadeClassifier *pc) { mpCascade = pc; }
inline cv::CascadeClassifier *Objdet::cascade() { Q_ASSERT(mpCascade); return mpCascade; }

