#pragma once

#include <QLine>
#include <QPoint>
#include <QSize>

#include "SCRect.h"

class SCLine
{
public: // ctors
    SCLine();
    SCLine(const SCRect l, const SCRect r);
    SCLine(const QSize sz, const QPoint l, const QPoint r);

public: // const
    SCRect lt() const;
    SCRect rt() const;
    QPoint lc() const;
    QPoint rc() const;
    SCLine offsetBy(const QPoint pt) const;
    QLine toQLine() const;

public: // non-const
    SCRect lt(const SCRect l);
    SCRect rt(const SCRect r);

private:
    SCRect mLeft, mRight;
};

inline SCRect SCLine::lt() const { return mLeft; }
inline SCRect SCLine::rt() const { return mRight; }
inline QPoint SCLine::lc() const { return lt().center(); }
inline QPoint SCLine::rc() const { return rt().center(); }
inline SCRect SCLine::lt(const SCRect l) { return mLeft = l; }
inline SCRect SCLine::rt(const SCRect r) { return mRight = r; }
