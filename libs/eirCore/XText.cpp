#include "XText.h"

#include <ctype.h>

char XText::smHingeChar = ' ';

XText::XText() {;}
XText::XText(const char *pch) : AText(pch) {;}
XText::XText(const QByteArray &ba) : AText(ba) {;}
XText::XText(const QString &s) : AText(s) {;}
XText::XText(const void *p, const Count k) { set(p,k); }

void XText::set(const void *p, const Count k)
{
    QByteArray tBA((const char *)(p), k);
    AText::set(tBA.toHex());
}

bool XText::isValidFirst(const char ch) const
{
    return isxdigit(ch);
}

bool XText::isValidChar(const char ch) const
{
    return isxdigit(ch);
}
