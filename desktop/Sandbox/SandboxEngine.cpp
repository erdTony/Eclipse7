#include "SandboxEngine.h"

#include <QTimer>
#include <QDateTime>

#include <Size.h>
#include <Point.h>
#include <Rgba32Table.h>

#include "SandboxApplication.h"
#include "SandboxScene.h"

SandboxEngine::SandboxEngine(SandboxApplication *parent)
    : QObject(parent)
    , mpApplication(parent)
    , mpProcessTimer(new QTimer(this))
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("SandboxEngine");
}

void SandboxEngine::initialize()
{
    qInfo() << Q_FUNC_INFO;

}

void SandboxEngine::setup()
{
    qInfo() << Q_FUNC_INFO;
    setupColorTable();
}

void SandboxEngine::start()
{
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpProcessTimer);
    Q_ASSERT(connect(mpProcessTimer, &QTimer::timeout,
                     this, &SandboxEngine::processOnce));
    mpProcessTimer->start(1000);
    emit started();
}

void SandboxEngine::process()
{
    bool tChanged = true;
    while (tChanged)
        tChanged = processOnce();
}

void SandboxEngine::setSubjectImage(const ColorImage &aCP)
{
    qInfo() << Q_FUNC_INFO << scene()->viewRect();
    const QImage cBaseIn = aCP.baseImage();
    const QRect cCropRect = scene()->viewRect().toQRect();
    const QImage cBaseCrop = cBaseIn.copy(cCropRect);
    const ColorImage cColorImage(cBaseCrop);
    mSubjectImage.set(cColorImage);
    SCRect cImageRect(cColorImage.rect());
    Size cImageSize = cImageRect.size();
    QImage tIndexImage(cImageSize, QImage::Format_Indexed8);
    tIndexImage.setColorTable(mColorTable);
    for (int rx = 0; rx < cImageSize.height(); ++rx)
        for (int cx = 0; cx < cImageSize.width(); ++cx)
        {
            const Point cPoint(rx, cx);
            const QRgb cRgbIn = cColorImage.pixel(cPoint);
            const BYTE cGrey = qGray(cRgbIn);
            tIndexImage.setPixel(cPoint, cGrey);
        }
    qInfo() << "Saving IndexImage.png:"
            << tIndexImage.save("IndexImage.png");
    mPreviousIndexedImage = IndexedImage(tIndexImage);
    scene()->set(SandboxScene::OldSubject, mPreviousIndexedImage.baseImage());
    scene()->set(SandboxScene::OldSubject, tIndexImage);
}

bool SandboxEngine::processOnce()
{
    qInfo() << Q_FUNC_INFO
            << QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    bool result = false;
    mPreviousIndexedImage = mCurrentIndexedImage;
    const Index cWidth = mCurrentIndexedImage.size().width();
    const Index cLastRowIx = mCurrentIndexedImage.size().height() - 1;
    for (Index tRow = cLastRowIx; tRow > 0; --tRow)
    {
        const Index cStartColIx = (cLastRowIx & 1) ? (cWidth - 1) : 0;
        const Index cFinisColIx = (cLastRowIx & 1) ? 0 : (cWidth - 1);
        const Index cStep = (cLastRowIx & 1) ? -1 : +1;
        for (Index tCol = cStartColIx; tCol != cFinisColIx; tCol += cStep)
        {
            const Point cDestPoint(int(tCol), (int)(tRow));
            const BYTE cPixelBelow = mPreviousIndexedImage.baseImage().pixel(cDestPoint);
            const BYTE cPixelAbove = mPreviousIndexedImage.baseImage().pixel(cDestPoint.up());
            const bool cSwap = cPixelBelow > cPixelAbove;
            result |= cSwap;
            mCurrentIndexedImage.baseImage().setPixel(cDestPoint, cSwap ? cPixelAbove : cPixelBelow);
            mCurrentIndexedImage.baseImage().setPixel(cDestPoint.up(), cSwap ? cPixelBelow : cPixelAbove);
        }
    }
    scene()->set(SandboxScene::NewSubject, mCurrentIndexedImage);
    return result;
}

SandboxScene *SandboxEngine::scene()
{
    return app()->scene();
}

QObject *SandboxEngine::object()
{
    return parent();
}


void SandboxEngine::setupColorTable()
{
    mColorTable.fill(QColor(Qt::transparent).rgba(), 256);
    setupColorTableLinear(  0,   3, 240, /* Low */
        QColor(0x10, 0x10, 0x10), QColor(0x30, 0x30, 0x30));
    setupColorTableLinear(236, 255, 240, /* High */
        QColor(0xC0, 0xC0, 0xC0), QColor(0xF0, 0xF0, 0xF0));
    setupColorTableLinear(  4,  19, 240, /* Bronze */
        QColor(0x5F, 0x3F, 0x22), QColor(0x7F, 0x5F, 0x42));
    setupColorTableLinear(236, 251, 240, /* Silver */
        QColor(0xB0, 0xB0, 0xB0), QColor(0xC0, 0xC0, 0xC0));
    setupColorTableLinear(120, 135, 240, /* Gold */
        QColor(0x90, 0x40, 0x00), QColor(0xCF, 0x7F, 0x2F));
#if 1
    setupColorTableLinear( 20, 119, 240, /* Sand */
        QColor( 48,  48,  16), QColor(151, 151,  48));
    setupColorTableLinear(136, 235, 240, /* Water */
        QColor( 32, 128, 128), QColor(64, 231, 231));
#else
    setupColorTableBilinear( 16, 119, 160, /* Sand */
                            QColor(0x00, 0x20, 0x20),
                            QColor(0x00, 0x50, 0x50),
                            QColor(0x50, 0x70, 0x70));
    setupColorTableBilinear(136, 239, 80, /* Water */
                            QColor(0xD6, 0xB0, 0x69),
                            QColor(0xEC, 0xCC, 0xA2),
                            QColor(0xFF, 0xF0, 0xDB));
#endif
#if 1
    for (Index ix = 0; ix < 255; ix += 8)
        qDebug() << Qt::dec << ix << Qt::hex
                 << mColorTable[ix+0] << mColorTable[ix+1]
                 << mColorTable[ix+2] << mColorTable[ix+3]
                 << mColorTable[ix+4] << mColorTable[ix+5]
                 << mColorTable[ix+6] << mColorTable[ix+7];
#endif
}

void SandboxEngine::setupColorTableLinear(const BYTE aFrom,
                                          const BYTE aTo,
                                          const BYTE aOpacity,
                                          const QColor aLoColor,
                                          const QColor aHiColor)
{
    QColor tColor;
    tColor.setAlpha(aOpacity);
    const float cIxDeltaF = aTo - aFrom,
                cRedLo = aLoColor.redF(),   cRedHi = aHiColor.redF(),
                cGrnLo = aLoColor.greenF(), cGrnHi = aHiColor.greenF(),
                cBluLo = aLoColor.blueF(),  cBluHi = aHiColor.blueF();
    const float cRedDelta = (cRedHi - cRedLo) / cIxDeltaF,
                cGrnDelta = (cGrnHi - cGrnLo) / cIxDeltaF,
                cBluDelta = (cBluHi - cBluLo) / cIxDeltaF;
    float tDltF = 0.0;
    for (Index ix = aFrom; ix <= aTo; ++ix)
    {
        const float cRedF = cRedLo + tDltF * cRedDelta,
                    cGrnF = cGrnLo + tDltF * cGrnDelta,
                    cBluF = cBluLo + tDltF * cBluDelta;
        tColor.setRedF(cRedF), tColor.setGreenF(cGrnF), tColor.setBlueF(cBluF);
        const QRgb cRgba = tColor.rgba();
        mColorTable[ix] = cRgba;
        tDltF += 1.0;
    }
}

void SandboxEngine::setupColorTableBilinear(const BYTE aFrom,
                                            const BYTE aTo,
                                            const BYTE aOpacity,
                                            const QColor aLoColor,
                                            const QColor aMidColor,
                                            const QColor aHiColor)
{
    const BYTE cMidIx = aFrom + aTo / 2;
    setupColorTableLinear(aFrom,  cMidIx, aOpacity, aLoColor, aMidColor);
    setupColorTableLinear(cMidIx, aTo,    aOpacity, aMidColor, aHiColor);
    mColorTable[cMidIx] = aMidColor.rgb();
}

#if 0
BrightnessContrast SandboxEngine::processHistogram(const Grey16Image aGrey16Image)
{
    qInfo() << Q_FUNC_INFO;
    BrightnessContrast result;

    // Gather Histogram
    WORD * pGrey16Data = (WORD *)aGrey16Image.baseImage().constBits();
    const Count nPixel = QQSize(aGrey16Image.baseImage().size()).area();
    Count kPixel = 0;
    do
    {
        const WORD cGrey16Pixel = *pGrey16Data++;
        mGrey8Histogram.add(cGrey16Pixel >> 8);
    } while (++kPixel < nPixel);

    // Trim tails from histogram
    const Count cTailBinCount = nPixel / 16;
    const Index cAllBinCount = mGrey8Histogram.binCount();
    Count tTailCount = 0;
    Index tBinIndex = 0;
    while (tTailCount < cTailBinCount && tBinIndex < cAllBinCount)
        tTailCount += mGrey8Histogram[tBinIndex++];
    const BYTE tLoBin = tBinIndex;

    tTailCount = 0;
    tBinIndex = cAllBinCount - 1;
    while (tTailCount < cTailBinCount && tBinIndex > 0)
        tTailCount += mGrey8Histogram[tBinIndex--];
    const BYTE tHiBin = tBinIndex;

    result.set(tLoBin, tHiBin);
    return result;
}
#endif
