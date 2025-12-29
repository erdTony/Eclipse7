#include "UrlType.h"

DEFINE_ENUMERATION(UrlType, URLTYPE_ENUM);

bool UrlType::isFile() const
{
    return value() == File || value() == Files || value() == TextFile;
}
