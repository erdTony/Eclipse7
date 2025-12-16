#include "EightCC.h"

#ifndef Q_CC_MSVC
EightCC::EightCC() { clear(); }
EightCC::EightCC(const char *pch) : Bytes(pch) {;}
EightCC::EightCC(const AText &atx) : Bytes(atx) {;}
EightCC::EightCC(const QString &s) : Bytes(s) {;}
EightCC::EightCC(const QWORD ow) : Bytes(ow) {;}
#endif
