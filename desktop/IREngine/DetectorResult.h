#pragma once

#include <QColor>
#include <QList>
#include <QPointF>
#include <QRect>
#include <QSizeF>

#include "SCRect.h"

class DetectorResult
{
public: // types
    typedef QList<DetectorResult> List;

public: // ctors
    DetectorResult(const QRect rect=QRect(), const int count=0);

public: // const
    int rank(void) const { return mRank; }
    int quality(void) const { return mQuality; }
    SCRect rect(void) const { return mResultRect; }
    int count(void) const { return mResultCount; }
    QList<SCRect> includedRects(void) const { return mIncludedRects; }
    SCRect includedRect(const int ix) const;
    QList<QRect> includedQRects(void) const;
    QColor frontalQualityColor(const int midQuality=500) const;
    QColor frontalQualityTextColor(const int midQuality=500) const;
    QColor eyeQualityColor(const int midQuality=500) const;

public: // non-const
    SCRect & rect() { return mResultRect; }
    void rank(const int r) { mRank = r; }
    void quality(const int q) { mQuality = q; }
    void count(const int k) { mResultCount = k; }
    void includedRects(const QList<SCRect> inc) { mIncludedRects = inc; }
    QList<SCRect> takeIncludedRects(const QList<SCRect> ar);

public: // debug
    QStringList toDebugStrings(const bool all=false) const;

private:
    int mRank;
    int mQuality;
    SCRect mResultRect;
    int mResultCount;
    QList<SCRect> mIncludedRects;
};
