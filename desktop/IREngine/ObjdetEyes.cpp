#include "ObjdetEyes.h"

#include "IfSearchWindow.h"
/*
ObjdetEyes::ObjdetEyes(QObject *parent)
    : Objdet{Objdet::Eyes, parent}
{
    setObjectName("ObjdetEyes:Null");
}
*/
ObjdetEyes::ObjdetEyes(const Class eye, QObject *parent)
    : Objdet{eye, parent}
{
    setObjectName("ObjdetEyes:" + (EyeRight == cmClass) ? "Right" : "Left");
}

ObjdetEyes::ObjdetEyes(const Objdet::Class eye,
                       const QImage &frame,
                       const DetectorResult &faceDR,
                       QObject *parent)
    : Objdet{eye, parent}
    , mInputFrame(frame)
    , mFaceResult(faceDR)
{
    setObjectName("ObjdetEyes:" + (EyeRight == cmClass) ? "Right" : "Left");
}

void ObjdetEyes::detectEye()
{
    clear();
    calculateEyeRoi(); // TODO Parm EyeOverCrop
    generateEyeImage();

}
/*
void ObjdetEyes::inputImage(const QImage &img, const QRect rc)
{

}
*/
SCRect ObjdetEyes::calculateEyeRoi(const unsigned overCrop)
{
    SCRect result;
    const SCRect cFaceRect = mFaceResult.rect();
    const unsigned cHalfFaceWidth = cFaceRect.width() / 2;
    const QPoint cFaceEyeRoiCenter
        = QPoint(cFaceRect.x() + (isRight() ? +cHalfFaceWidth : -cHalfFaceWidth),
                 cFaceRect.y() - cFaceRect.height() / 2);
    SCRect tFaceEyeRect(cFaceRect.size() / 2, cFaceEyeRoiCenter);
    if (overCrop) tFaceEyeRect *= 1.0 + (qreal(overCrop) / 100.0);
    SCRect tFrameEyeRect(tFaceEyeRect.size(),
                         cFaceRect.center() + tFaceEyeRect.center());
    result = tFrameEyeRect; // & mInputFrame.rect();
    qInfo() << Q_FUNC_INFO << isRight() << mInputFrame.rect()
            << cFaceRect << cHalfFaceWidth << cFaceEyeRoiCenter
            << tFaceEyeRect << tFrameEyeRect << result;
    return mFrameEyeRect = result;
}

void ObjdetEyes::generateEyeImage()
{
    const int cThumbWidth = IfSearchWindow::faceThumbSize().width();
    mDetectScale = (mFrameEyeRect.width() > cThumbWidth) ? 1
        : int(0.999 + qreal(cThumbWidth) / qreal(mFrameEyeRect.width()));
    mFrameEyeRect *= mDetectScale;
    mFrameEyeRect = mFrameEyeRect.trimmed(16);
    mEyeImage = mInputFrame.scaledToWidth(mInputFrame.width() * mDetectScale)
                           .copy(mFrameEyeRect);
    qInfo() << Q_FUNC_INFO << mInputFrame.size() << mDetectScale
            << mFrameEyeRect.toDebugString() << mEyeImage.size();
    Objdet::inputImage(mEyeImage);
}
