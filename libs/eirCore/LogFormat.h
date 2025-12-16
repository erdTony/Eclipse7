#pragma once
#include "eirCore.h"

class CText;
class CTextList;

class LogItem;

class EIRCORE_EXPORT LogFormat
{
public: // types
    enum Format
    {
        $nullFormat     = 0,
        TextOneLine     = 0x0001,
        TextMultiLine   = 0x0002,
        XmlDocument     = 0x0010,
        SqlRecord       = 0x0100,
    };

public: // ctors
    LogFormat(const Format fmt=$nullFormat);

public: // const
    CTextList process(const LogItem &li) const;

public: // non-const
    void set(const CText &tx);

public: // pointers

private:
    CTextList processOneText(const LogItem &li) const;
    CTextList processMultiText(const LogItem &li) const;
    CTextList processXmlDocument(const LogItem &li) const;
    CTextList processSqlRecord(const LogItem &li) const;

private:
    Format mFormat;

};
