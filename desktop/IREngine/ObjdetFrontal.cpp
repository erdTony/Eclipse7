#include "ObjdetFrontal.h"

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QRect>

#include "DetectorResult.h"
#include "DetectorResultList.h"

ObjdetFrontal::ObjdetFrontal(QObject *parent)
    : Objdet{Objdet::FaceFrontal, parent}
{
    setObjectName("ObjdetFrontal");
}

QImage ObjdetFrontal::markedImage(const SCRect eyeLRect, const SCRect eyeRRect,
                                  int minQuality, int showQuality) const
{
    QImage result = inputImage();
    if (minQuality  <= 0) minQuality  = 500;
    if (showQuality <= 0) showQuality = minQuality / 2;
    QPainter tPainter;
    tPainter.begin(&result);
    tPainter.setFont(QFont("helvetica", 16));
    DetectorResult::List tResultList = resultList().rankedList();
    qInfo() << Q_FUNC_INFO << inputImage().size() << tResultList.count()
            << eyeLRect.toDebugString() << eyeRRect.toDebugString();
    while ( ! tResultList.isEmpty())
    {
        const DetectorResult cResult = tResultList.takeLast();
        const QRect cRect = cResult.rect();
        const int cRank = cResult.rank();
        const int cQuality = cResult.quality();
        qDebug() << cRank << cQuality << cResult.rect().toDebugString();
        if (cQuality >= showQuality)
        {
            const QString cTitle
                = QString("#%1 Q%2")
                      .arg(cRank)
                      .arg(cQuality, 3, 10, QChar('0'));
            const QColor cColor = cResult.frontalQualityColor(minQuality);
            QPen tPen(QBrush(cColor), 7);
            tPainter.setPen(tPen);
            tPainter.drawRect(cRect);
            tPen = QPen(Qt::yellow, 1);
            tPainter.setPen(tPen);
            if ( ! eyeLRect.isNull()) tPainter.drawRect(eyeLRect.toQRect());
            if ( ! eyeRRect.isNull()) tPainter.drawRect(eyeRRect.toQRect());
            const QRect cTitleRect(QPoint(cRect.left() - 4,
                                          cRect.top() - 24),
                                   QPoint(cRect.right() + 4,
                                          cRect.top()));
            tPainter.fillRect(cTitleRect, cColor);
            tPainter.setPen(cResult.frontalQualityTextColor(minQuality));
            //            tPainter.setBackground(cColor);
            tPainter.drawText(cTitleRect.bottomLeft(), cTitle);
        }
    }
    tPainter.end();
    return result;
}

QImage ObjdetFrontal::detectImage(const unsigned minQuality) const
{
    QImage result = inputImage()
                        .convertedTo(QImage::Format_Grayscale8)
                        .convertedTo(QImage::Format_ARGB32);
    QPainter tPainter;
    tPainter.begin(&result);
    tPainter.setPen(Qt::magenta);
    tPainter.drawRects(resultList().orphanQRects());
    tPainter.setFont(QFont("helvetica", 16));
    DetectorResult::List tResultList = resultList().rankedList();
    qDebug() << Q_FUNC_INFO << inputImage().size() << tResultList.count()
             << (tResultList.isEmpty() ? 0 : tResultList.first().quality())
             << resultList().orphanList().count();
    while ( ! tResultList.isEmpty())
    {
        const DetectorResult cResult = tResultList.takeLast();
        const QRect cRect = cResult.rect();
        const int cRank = cResult.rank();
        const int cQuality = cResult.quality();
        const int cCount = cResult.count();
        const QString cTitle
            = QString("#%1 Q%2 K%3 W%4")
                  .arg(cRank)
                  .arg(cQuality, 3, 10, QChar('0'))
                  .arg(cCount)
                  .arg(cRect.width());
        const QColor cColor = cResult.frontalQualityColor(minQuality);
        QPen tPen(QBrush(cColor), 1);
        tPainter.setPen(tPen);
        tPainter.drawRects(cResult.includedQRects());
        tPen.setWidth(7);
        tPainter.setPen(tPen);
        tPainter.drawRect(cRect);
        const QRect cTitleRect(QPoint(cRect.left() - 4,
                                      cRect.top() - 24),
                               QPoint(cRect.right() + 4,
                                      cRect.top()));
        tPainter.fillRect(cTitleRect, cColor);
        tPainter.setPen(cResult.frontalQualityTextColor(minQuality));
        tPainter.setBackground(cColor);
        tPainter.drawText(cTitleRect.bottomLeft(), cTitle);
    }
    tPainter.end();
    return result;
}

