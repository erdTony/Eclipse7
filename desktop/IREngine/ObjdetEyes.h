#pragma once

#include <QObject>
#include "Objdet.h"

#include <QImage>

#include "DetectorResult.h"
#include "DetectorResultList.h"
#include "SCRect.h"

class ObjdetEyes : public Objdet
{
    Q_OBJECT
public: // ctors
//    explicit ObjdetEyes(QObject *parent = nullptr);
    ObjdetEyes(const Objdet::Class eye,
                        QObject *parent = nullptr);
    ObjdetEyes(const Objdet::Class eye,
                        const QImage &frame,
                        const DetectorResult &faceDR,
                        QObject *parent = nullptr);

public slots:
    void detectEye();

public: // const
    bool isRight() const;
    SCRect eyeRect() const;
    QImage eyeImage() const;

public: // non-const
//    void inputImage(const QImage &img, const QRect rc);
    SCRect calculateEyeRoi(const unsigned int overCrop=0);
    void generateEyeImage();

public: // pointers

private:
    QImage mInputFrame;
    DetectorResult mFaceResult;
    QImage mEyeImage;
    SCRect mFrameEyeRect;
    int mDetectScale=0;
};

inline bool ObjdetEyes::isRight() const { return Objdet::EyeRight == cmClass; }
inline SCRect ObjdetEyes::eyeRect() const { return mFrameEyeRect; }
inline QImage ObjdetEyes::eyeImage() const { return mEyeImage; }

