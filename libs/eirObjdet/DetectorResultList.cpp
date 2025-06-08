#include "DetectorResultList.h"

#include <QtDebug>

#include "ObjdetRawArguments.h"

DetectorResultList::DetectorResultList() {;}

DetectorResultList::DetectorResultList(const ObjdetRawArguments raw,
                                       const std::vector<cv::Rect> rects,
                                       const std::vector<int> counts,
                                       const std::vector<cv::Rect> allrects)
    : mCvRects(rects)
    , mCvCounts(counts)
    , mAllCvRects(allrects)
{
    calculate(raw);
}

int DetectorResultList::count(const int minQuality) const
{
    int result = 0;
    foreach (const DetectorResult cDR, mRankedList)
        if (cDR.quality() >= minQuality) ++result;
    return result;
}

QList<QRect> DetectorResultList::orphanQRects() const
{
    QList<QRect> result;
    foreach (const SCRect cSCR, orphanList())
        result << cSCR.toQRect();
    return result;
}

void DetectorResultList::process(const ObjdetRawArguments raw,
                                 const std::vector<cv::Rect> rects,
                                 const std::vector<int> counts,
                                 const std::vector<cv::Rect> allrects)
{
    mCvRects = rects, mCvCounts = counts, mAllCvRects = allrects;
    calculate(raw);
}

void DetectorResultList::calculate(const ObjdetRawArguments raw)
{
    clearResults();
    if (0 == mCvRects.size()
            || 0 == mCvCounts.size()
            || mCvRects.size() != mCvCounts.size())
        qCritical() << "Rects/Counts mismatch"
                    << mCvRects.size() << mCvCounts.size();
    for (unsigned ix = 0; ix < mAllCvRects.size(); ++ix)
        mAllRectList << SCRect(QSize(mAllCvRects.at(ix).width,
                                     mAllCvRects.at(ix).height),
                               QPoint(mAllCvRects.at(ix).tl().x,
                                      mAllCvRects.at(ix).tl().y));

    const unsigned cItemCount = qMin(mCvRects.size(), mCvCounts.size());
    for (unsigned ix = 0; ix < cItemCount; ++ix)
    {
        const SCRect cObjdetRect(QSize(mAllCvRects.at(ix).width,
                                       mAllCvRects.at(ix).height),
                                 QPoint(mAllCvRects.at(ix).tl().x,
                                        mAllCvRects.at(ix).tl().y));
        const int cObjdetCount = mCvCounts.at(ix);

        // MUSTDO MUCHO
        Q_UNUSED(raw);
        Q_UNUSED(cObjdetRect); Q_UNUSED(cObjdetCount);
    }

}

void DetectorResultList::addRanked(const DetectorResult &dr)
{
    mRankedList.append(dr);
}

void DetectorResultList::adjustRanked(const SCRect rcOffset, const int scale)
{
    DetectorResult::List result;
    foreach (DetectorResult dr, rankedList())
    {
        dr.rect().scale(1.0 / qreal(scale));
        dr.rect().offset(rcOffset.center());
        QList<SCRect> included;
        foreach(SCRect rc, dr.includedRects())
        {
            rc.scale(1.0 / qreal(scale));
            rc.offset(rcOffset.center());
            included << rc;
        }
        dr.includedRects(included);
        result << dr;
    }
    rankedList(result);
}

void DetectorResultList::clearAll()
{
    clearInputs(), clearResults();
}

void DetectorResultList::clearInputs()
{
    mCvRects.clear(), mCvCounts.clear(), mAllCvRects.clear();
}

void DetectorResultList::clearResults()
{
    mRankedList.clear(), mAllRectList.clear(), mOrphanRectList.clear();
}

QStringList DetectorResultList::toDebugStrings(const bool all) const
{
    QStringList result;
    result << "===DetectorResultList: {";
    const int nList = mRankedList.count();
    for (int ix = 0; ix < nList; ++ix)
        result << QString("   %1. %2").arg(ix + 1, 2)
                      .arg(at(ix).toDebugStrings(all).join(QChar('\n')));
    result << "===}";
    return result;
}

QDebug &operator<<(QDebug &stream, const DetectorResultList drl)
{
    stream << drl.toDebugStrings().join('\n'); return stream;
    return stream;
}

