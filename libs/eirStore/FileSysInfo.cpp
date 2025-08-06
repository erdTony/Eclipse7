#include "FileSysInfo.h"

#if defined( Q_OS_WINDOWS ) // 32 or 64 bit
FileSysInfo::Mode FileSysInfo::smDefaultMode = FileSysInfo::Windows;
#elif defined( Q_OS_ANDROID )
FileSysInfo::Mode FileSysInfo::smDefaultMode = FileSysInfo::Android;
#elif defined( Q_OS_LINUX ) || defined( Q_OS_UNIX )
FileSysInfo::Mode FileSysInfo::smDefaultMode = FileSysInfo::Linux;
#elif defined( Q_OS_BSD4 ) || defined( Q_OS_FREEBSD ) || defined( Q_OS_NETBSD ) || defined( Q_OS_OPENBSD )
FileSysInfo::Mode FileSysInfo::smDefaultMode = FileSysInfo::BSD;
#else
FileSysInfo::Mode FileSysInfo::smDefaultMode = FileSysInfo::$null;
#endif

FileSysInfo::FileSysInfo() : cmMode(defaultMode()) {;}
FileSysInfo::FileSysInfo(const Mode forceMode) : cmMode(forceMode) {;}

char FileSysInfo::fileSegmentSeparator() const
{
    char result = '?';
    switch (mode())
    {
    case Linux:
    case Windows:   result = '.';           break;
    case BSD:       /* TODO BSD */
    case Android:   /* TODO Android */
    case $null:
    default:                                break;
    }
    return result;
}

char FileSysInfo::directoryPathSeparator() const
{
    char result = '?';
    switch (mode())
    {
    case Linux:     result = '/';           break;
    case Windows:   result = '\\';          break;
    case BSD:
    case Android:
    case $null:
    default:                                break;
    }
    return result;
}

char FileSysInfo::directoryListSeparator() const
{
    char result = '?';
    switch (mode())
    {
    case Linux:     result = ':';           break;
    case Windows:   result = ';';           break;
    case BSD:
    case Android:
    case $null:
    default:                                break;
    }
    return result;
}

bool FileSysInfo::isCaseSensitive() const
{
    bool result = false;
    switch (mode())
    {
    case Linux:     result = true;          break;
    case Windows:   result = false;         break;
    case BSD:
    case Android:
    case $null:
    default:                                break;
    }
    return result;
}

bool FileSysInfo::hasColonDrive() const
{
    bool result = false;
    switch (mode())
    {
    case Linux:     result = false;         break;
    case Windows:   result = true;          break;
    case BSD:
    case Android:
    case $null:
    default:                                break;
    }
    return result;
}


