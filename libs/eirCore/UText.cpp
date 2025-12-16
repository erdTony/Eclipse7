#include "UText.h"

UText::UText() {;}
UText::UText(const char *pch) : QString(pch) {;}
UText::UText(const QByteArray &ba)  : QString(ba) {;}
UText::UText(const QString &other)  : QString(other) {;}

