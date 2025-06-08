#include "DetectorResult.h"


DetectorResult::DetectorResult(const QRect rect, const int count)
    : mRank(0)
    , mQuality(0)
    , mResultRect(rect)
    , mResultCount(count)
{

}

SCRect DetectorResult::includedRect(const int ix) const
{
    return (ix >= 0 && ix < includedRects().count())
               ? includedRects().at(ix) : SCRect();
}

QList<QRect> DetectorResult::includedQRects() const
{
    QList<QRect> result;
    foreach (const SCRect cSCR, includedRects())
        result << cSCR.toQRect();
    return result;
}

QColor DetectorResult::frontalQualityColor(const int midQuality) const
{
    QColor result(Qt::black);
    if (quality() > midQuality)
        result = QColor(Qt::cyan).lighter(100 + ((quality() - midQuality) / 10));
    else
        result = QColor(Qt::blue).darker(100 + ((midQuality - quality()) / 10));
    return result;
}

QColor DetectorResult::frontalQualityTextColor(const int midQuality) const
{
    QColor result(Qt::black);
    if (quality() > midQuality)
        result = QColor(Qt::darkYellow);
    else
        result = QColor(Qt::yellow);
    return result;
}

QColor DetectorResult::eyeQualityColor(const int midQuality) const
{
    QColor result(Qt::black);
    if (quality() > midQuality)
        result = QColor(Qt::yellow).lighter(100 + ((quality() - midQuality) / 10));
    else
        result = QColor(Qt::darkYellow).darker(100 + ((midQuality - quality()) / 10));
    return result;
}

QList<SCRect> DetectorResult::takeIncludedRects(const QList<SCRect> ar)
{
    QList<SCRect> result;
    const int cMinWidth = qreal(rect().width()) / 1.3;
    const int cMaxWidth = qreal(rect().width()) * 1.3;
    foreach (const SCRect rc, ar)
        if (rect().contains(rc.center())
                && rc.width() > cMinWidth
                && rc.width() < cMaxWidth)
            mIncludedRects << rc;
        else
            result << rc;
    return result;
}

QStringList DetectorResult::toDebugStrings(const bool all) const
{
    QStringList result;
    result << "   ---DetectorResult: {";
    result << QString("      #%1 Q%2 %3 K%4")
                  .arg(rank(), 2, 10, QChar('0'))
                  .arg(rank(), 3, 10, QChar('0'))
                  .arg(rect().toDebugString())
                  .arg(count());
    const int kInc = includedRects().count();
    if (all)
        for(int ix = 0; ix < kInc; ++ix)
            result << QString("      %1. %2").arg(ix, 3)
                          .arg(includedRect(ix).toDebugString());
    result << "   ---}";
    return result;
}

