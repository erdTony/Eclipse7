#include "XText.h"

#include <ctype.h>

char XText::smHingeChar = ' ';

XText::XText() {;}
XText::XText(const char *pch) : AText(pch) {;}
XText::XText(const QByteArray &ba) : AText(ba) {;}
XText::XText(const QString &s) : AText(s) {;}




