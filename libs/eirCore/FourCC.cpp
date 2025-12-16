#include "FourCC.h"

FourCC::FourCC() { clear(); }
FourCC::FourCC(const char *pch) : Bytes(pch) {;}
FourCC::FourCC(const AText &atx) : Bytes(atx) {;}
FourCC::FourCC(const QString &s) : Bytes(s) {;}
