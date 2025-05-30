// @file IfSearch.h
#pragma once

#include <QObject>

#include <QDateTime>
#include <QDir>
#include <QFileInfoList>
#include <QList>
#include <QImage>

#include "DetectorResultList.h"
#include "IfSearchApplication.h"
#include "Objdet.h"
#include "SCRect.h"
#include "SCLine.h"
#include "VersionInfo.h"

class ObjdetCatalog;
class ObjdetEyes;
class ObjdetFrontal;

class IfSearchEngine : public QObject
{
    Q_OBJECT

public: // ctors
    IfSearchEngine(IfSearchApplication * parent=nullptr);
    ~IfSearchEngine();

public: // const
    IfSearchApplication::Options options() const;

public: // non-const

public: // pointers
    IfSearchApplication * app();
    IfSearchApplication * app() const;
    ObjdetEyes * eyeObjdet(const Objdet::Class objcls);

private:
    void processFrame(const QFileInfo &fi);
    void processFaces();
    int scanInputDirectory();
    QImage readInputImage(const QFileInfo &fi);
    void writeFrameImages();
    SCRect calculateFaceRect();
    QImage extractFaceImage();
    bool writeFaceImage();
    DetectorResultList findEyeDRL(const Objdet::Class objcls);
    SCLine selectBestEyes(const DetectorResultList ltDRL,
                          const DetectorResultList rtDRL);
    SCRect calculateEyeRoi(const Objdet::Class objcls);
    void extractEyeImages();

private slots:
    void init(void);
    void start(void);
    void startFrontal(void);
    void startEyes(void);
    void run(void);
    void pulse(void);

private:
    IfSearchApplication * mpApplication=nullptr;
    ObjdetCatalog * mpObjdetCatalog=nullptr;
    ObjdetFrontal * mpFrontal=nullptr;
    ObjdetEyes * mpLEyes=nullptr;
    ObjdetEyes * mpREyes=nullptr;
    QDateTime mBaseTimestamp;
    QDir mInputDir;
    QDir mOutputBaseDir;
    QDir mMarkedDir;
    QDir mNoFaceDir;
    QDir mDetectedFacesDir;
    QDir mFrontalObjdetDir;
    QDir mEyesObjdetDir;
    QFileInfoList mInputFileList;
    // current frame
    QFileInfo mCurrentFrameFI;
    QImage mCurrentFrameImage;
    QImage mCurrentMarkedImage;
    QImage mCurrentDetectImage;
    DetectorResultList mFrameFaceDRL;
    // current face
    DetectorResult mCurrentFaceDR;
    SCRect mCurrentFaceRect;
    QImage mCurrentFaceImage;
    DetectorResult mCurrentFaceLEyeDR;
    DetectorResult mCurrentFaceREyeDR;
    SCLine mCurrentFrameEyeLine;
    QImage mLtEyeRoiImage;
    QImage mRtEyeRoiImage;

private:

private:
};

inline IfSearchApplication *IfSearchEngine::app() { return mpApplication; }

inline IfSearchApplication *IfSearchEngine::app() const {  Q_ASSERT(mpApplication); return mpApplication; }
inline IfSearchApplication::Options IfSearchEngine::options() const { return app()->options(); }


