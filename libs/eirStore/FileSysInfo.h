#pragma once

#include "Types.h"

class FileSysInfo
{
public: // types
    enum Mode
    {
        $null       = 0,
        Android     = 0x01,
        BSD         = 0x02,
        Linux       = 0x04,
        Windows     = 0x08,
    };

public:
    FileSysInfo();
    FileSysInfo(const Mode forceMode);


public: // const
    Mode mode() const;
    char fileSegmentSeparator() const;
    char directoryPathSeparator() const;
    char directoryListSeparator() const;
    bool isCaseSensitive() const;
    bool hasColonDrive() const;
    static Mode defaultMode();

public: // non-const
    static void defaultMode(const Mode mode);

private:
    const Mode cmMode;
    static Mode smDefaultMode;
};

inline FileSysInfo::Mode FileSysInfo::mode() const { return cmMode; }
inline FileSysInfo::Mode FileSysInfo::defaultMode() { return smDefaultMode; }
inline void FileSysInfo::defaultMode(const Mode mode) { smDefaultMode = mode; }
