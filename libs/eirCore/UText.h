#pragma once
#include "eirCore.h"

#include <QString>

class EIRCORE_EXPORT UText : public QString
{
public: //ctors
    UText();
    UText(const char * pch);
    UText(const QByteArray &ba);
    UText(const QString &other);

};
