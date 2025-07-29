#include "SandboxEngine.h"

#include <QByteArray>
#include <QTimer>
#include <QDateTime>

#include <cstring>

#include <ExeSupport.h>
#include <Point.h>
#include <Random.h>
#include <Rational.h>
#include <SCRect.h>
#include <Size.h>

#include "SandboxApplication.h"
#include "SandboxMainWindow.h"

SandboxEngine::SandboxEngine(SandboxApplication *parent)
    : QObject(parent)
    , mpApplication(parent)
    , mpSwapTimer(new QTimer(this))
{
    qInfo() << Q_FUNC_INFO;
    setObjectName("SandboxEngine");
}

void SandboxEngine::initialize()
{
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpSwapTimer);
    Q_ASSERT(connect(mpSwapTimer, &QTimer::timeout,
                     this, &SandboxEngine::processSwaps));
}

void SandboxEngine::setup()
{
    qInfo() << Q_FUNC_INFO;
    setupColorTable();
}

void SandboxEngine::start()
{
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpSwapTimer);
    Q_ASSERT(connect(this, &SandboxEngine::started,
                     this, &SandboxEngine::startFrame));
    Q_ASSERT(connect(mpSwapTimer, &QTimer::timeout,
                     this, &SandboxEngine::swapFrame));
    Q_ASSERT(connect(this, &SandboxEngine::frameSwapFinished,
                     this, &SandboxEngine::finishFrame));

    emit started();
}


void SandboxEngine::subjectImage(const QImage &qi)
{
    qInfo() << Q_FUNC_INFO << qi;
    const Size cImageSize = app()->mainWindow()->baseSize();
    const SCRect cBaseRect(cImageSize);
    const QImage cBaseImage = qi.copy(cBaseRect);
    mSubjectImage = cBaseImage;
    QImage tIndexImage(mSubjectImage.size(), QImage::Format_Indexed8);
    tIndexImage.fill(255);
    //tIndexImage.setColorTable(Rgba32Table::greyTable());
    tIndexImage.setColorTable(mColorTable);
    for (int rx = 0; rx < cImageSize.height(); ++rx)
        for (int cx = 0; cx < cImageSize.width(); ++cx)
        {
            const Point cPoint(rx, cx);
            const QRgb cRgbIn = cBaseImage.pixel(cPoint);
            const BYTE cGrey = qGray(cRgbIn);
            tIndexImage.setPixel(cPoint, qBound(BYTE(1), cGrey, BYTE(254)));
        }
    qDebug() << "Saving IndexImage.png:"
            << tIndexImage.save("IndexImage.png");
    processImage(tIndexImage);
}

void SandboxEngine::startFrame()
{
    qInfo() << Q_FUNC_INFO;
    mSwapCount = 0;
    Q_CHECK_PTR(mpSwapTimer);
    mpSwapTimer->start(50);
}

void SandboxEngine::swapFrame()
{
//    qInfo() << Q_FUNC_INFO;
    const Count cNumSwaps = processSwaps();
    const Size cImageSize(processImage().size());
    const Count cImageArea = cImageSize.area();
    const qreal cSwapsF = qreal(cNumSwaps) / qreal(cImageArea);
    ++mSwapCount;
    if ((cSwapsF < 0.17)
        || (mSwapCount >= Count(processImage().height())))
        emit frameSwapFinished();
    else
        emit frameSwapped(mSwapCount, cNumSwaps, processImage());
}

void SandboxEngine::finishFrame()
{
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpSwapTimer);
    mpSwapTimer->stop();
    QTimer::singleShot(500, this, &SandboxEngine::flipFrame);
}

void SandboxEngine::flipFrame()
{
    qInfo() << Q_FUNC_INFO;
    mProcessImage.flip();
    QTimer::singleShot(100, this, &SandboxEngine::startFrame);
    emit frameFlipped(processImage());
}

Count SandboxEngine::processSwaps()
{
    Count result = 0;
    QImage tImage = processImage();
    const Index cWidth = tImage.size().width();
    const Index cHeight = tImage.size().height();

    QByteArray tAboveRow(cWidth, 0);
    QByteArray tBelowRow((const char *)tImage.constScanLine(0), cWidth);
    for (int tRow = 1; tRow < cHeight; ++tRow)
    {   // downward from second row
        tAboveRow = tBelowRow;
        tBelowRow = QByteArray((const char *)tImage.constScanLine(tRow), cWidth);
        const UIntList cRandomCols = app()->exe()->rand()->take(cWidth, cWidth);
        for (int tColIx = 1; tColIx < cWidth - 1; ++tColIx)
        {
            int tCol = qBound(1U, cRandomCols[tColIx], UINT(cWidth-2));
            BYTE tAboveValue = tAboveRow[tCol];
            BYTE tAboveLeft =  tAboveRow[tCol - 1], tAboveRight =  tAboveRow[tCol + 1];
            BYTE tBelowLeft = tBelowRow[tCol - 1], tBelowValue = tBelowRow[tCol], tBelowRight = tBelowRow[tCol + 1];
            BYTE tBelowLightest = qMax(tBelowValue, qMax(qMax(tAboveLeft, tAboveRight), qMax(tBelowLeft, tBelowRight)));
            if (tBelowLightest > tAboveValue)
            {
                ++result;
                if (tBelowLightest == tBelowValue)
                    qSwap(tAboveRow[tCol], tBelowRow[tCol]);
                else if (tBelowLightest == tBelowLeft)
                    qSwap(tAboveRow[tCol], tBelowRow[tCol - 1]);
                else if (tBelowLightest == tBelowRight)
                    qSwap(tAboveRow[tCol], tBelowRow[tCol + 1]);
                else if (tBelowLightest == tAboveLeft)
                    qSwap(tBelowRow[tCol], tBelowRow[tCol + 1]);
                else if (tBelowLightest == tAboveRight)
                    qSwap(tBelowRow[tCol], tBelowRow[tCol + 1]);
            }
            tBelowValue = tBelowRow[tCol];
            // pushing sky up
            tAboveValue = tAboveRow[tCol];
            tBelowLeft =  tAboveRow[tCol - 1], tBelowRight =  tAboveRow[tCol + 1];
            tAboveLeft = tAboveRow[tCol - 1], tAboveRight = tAboveRow[tCol + 1];
            BYTE tAboveDarkest  = qMin(tAboveValue, qMin(qMin(tBelowLeft, tBelowRight), qMin(tAboveLeft, tAboveRight)));
            if (tAboveDarkest < tBelowValue)
            {
                ++result;
                if (tAboveDarkest == tAboveValue)
                    qSwap(tBelowRow[tCol], tAboveRow[tCol]);
                else if (tAboveDarkest ==  tAboveLeft)
                    qSwap(tBelowRow[tCol], tAboveRow[tCol - 1]);
                else if (tAboveDarkest ==  tAboveRight)
                    qSwap(tBelowRow[tCol], tAboveRow[tCol + 1]);
                else if (tAboveDarkest ==  tBelowLeft)
                    qSwap(tBelowRow[tCol], tBelowRow[tCol + 1]);
                else if (tAboveDarkest ==  tBelowRight)
                    qSwap(tBelowRow[tCol], tBelowRow[tCol + 1]);
            }
        }
        std::memcpy((void *)(tImage.scanLine(tRow - 1)), tAboveRow.constData(), cWidth);
    }
    std::memcpy((void *)(tImage.scanLine(cHeight - 1)), tBelowRow.constData(), cWidth);
    processImage(tImage);
    return result;
}






void SandboxEngine::setupColorTable()
{
    mColorTable.fill(QColor(Qt::transparent).rgba(), 256);
    setupColorTableLinear(  1,   3, 240, /* Low */
        QColor(0x10, 0x10, 0x10), QColor(0x30, 0x30, 0x30));
    setupColorTableLinear(236, 254, 240, /* High */
        QColor(0xC0, 0xC0, 0xC0), QColor(0xF0, 0xF0, 0xF0));
    setupColorTableLinear(  4,  19, 240, /* Bronze */
        QColor(0x5F, 0x3F, 0x22), QColor(0x7F, 0x5F, 0x42));
    setupColorTableLinear(236, 251, 240, /* Silver */
        QColor(0xB0, 0xB0, 0xB0), QColor(0xC0, 0xC0, 0xC0));
    setupColorTableLinear(120, 135, 240, /* Gold */
        QColor(0x90, 0x40, 0x00), QColor(0xCF, 0x7F, 0x2F));
    mColorTable[0] = QColor(Qt::transparent).rgba();
    mColorTable[255] = QColor(0, 0x40, 0).rgba();
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

