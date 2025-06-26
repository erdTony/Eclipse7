#pragma once
#include "eirBase.h"

#include <QString>

class EIRBASE_EXPORT UText : public QString
{
public: //ctors
    UText();
    UText(const char * pch);
    UText(const QByteArray &ba);
    UText(const QString &other);

};
