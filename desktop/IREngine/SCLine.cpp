#include "SCLine.h"

SCLine::SCLine() {;}
SCLine::SCLine(const SCRect l, const SCRect r) : mLeft(l), mRight(r) {;}
SCLine::SCLine(const QSize sz, const QPoint l, const QPoint r)
    : mLeft(sz, l), mRight(sz, r) {;}

SCLine SCLine::offsetBy(const QPoint pt) const
{
    SCRect tLtRect = lt(), tRtRect = rt();
    tLtRect.offset(pt), tRtRect.offset(pt);
    return SCLine(tLtRect, tRtRect);
}

QLine SCLine::toQLine() const
{
    return QLine(lt().center(), rt().center());
}
