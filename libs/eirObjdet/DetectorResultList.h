#pragma once

#include "DetectorResult.h"

#include <QList>
#include <QMultiMap>
#include <QRect>

#include <vector> // std::

#include <opencv2/core.hpp>

#include "ObjdetRawArguments.h"

class DetectorResultList
{
public: // typedef
    typedef QList<DetectorResultList> List;

public: // ctors
    DetectorResultList();
    DetectorResultList(const ObjdetRawArguments raw,
                       const std::vector<cv::Rect> rects,
                       const std::vector<int> counts,
                       const std::vector<cv::Rect> allrects
                            =std::vector<cv::Rect>());

public: // const
    int count() const;
    bool isEmpty() const;
    int count(const int minQuality) const;
    DetectorResult at(const int ix) const;
    DetectorResult best() const;
    DetectorResult::List rankedList() const;
    QList<SCRect> allRectList() const;
    QList<SCRect> orphanList() const;
    QList<QRect> orphanQRects() const;
    QList<SCRect> includedRects(const DetectorResult &result,
                               const QList<SCRect> &rects);

public: // non-const
    void process(const ObjdetRawArguments raw,
                 const std::vector<cv::Rect> rects,
                 const std::vector<int> counts,
                 const std::vector<cv::Rect> allrects
                    =std::vector<cv::Rect>());
    void calculate(const ObjdetRawArguments raw);
    void addRanked(const DetectorResult &dr);
    void rankedList(const DetectorResult::List rl);
    void orphanList(const QList<SCRect> ol);
    void adjustRanked(const SCRect rcOffset, const int scale);
    void clearAll();
    void clearInputs();
    void clearResults();

public: // debug
    QStringList toDebugStrings(const bool all=false) const;

private:
    std::vector<cv::Rect> mCvRects;
    std::vector<int> mCvCounts;
    std::vector<cv::Rect> mAllCvRects;
    DetectorResult::List mRankedList;
    QList<SCRect> mAllRectList;
    QList<SCRect> mOrphanRectList;
};

extern QDebug &operator<<(QDebug &stream, const DetectorResultList drl);

inline int DetectorResultList::count() const { return mRankedList.count(); }
inline bool DetectorResultList::isEmpty() const{ return 0 == count(); }
inline DetectorResult DetectorResultList::at(const int ix) const { return rankedList().at(ix); }
inline DetectorResult DetectorResultList::best() const { DetectorResult::List drl = rankedList(); return drl.first(); }
inline DetectorResult::List DetectorResultList::rankedList() const { return mRankedList; }
inline QList<SCRect> DetectorResultList::allRectList() const { return mAllRectList; }
inline QList<SCRect> DetectorResultList::orphanList() const { return mOrphanRectList; }
inline void DetectorResultList::rankedList(const DetectorResult::List rl)  { mRankedList = rl; }
inline void DetectorResultList::orphanList(const QList<SCRect> ol) { mOrphanRectList = ol; }


