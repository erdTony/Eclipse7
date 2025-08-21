#include "LogFormat.h"

#include <CText.h>
#include <CTextList.h>

#include "LogItem.h"
#include "LogItem.h"

LogFormat::LogFormat(const Format fmt) : mFormat(fmt) {;}

CTextList LogFormat::process(const LogItem &li) const
{
    CTextList result;
    switch (mFormat)
    {
    case TextOneLine:   result = processOneText(li);        break;
    case TextMultiLine: result = processMultiText(li);      break;
    case XmlDocument:   result = processXmlDocument(li);    break;
    case SqlRecord:     result = processSqlRecord(li);      break;
    default:            /* NADA */                          break;
    }
    return result;
}

CTextList LogFormat::processOneText(const LogItem &li) const
{
    CTextList result;
    result << CText(li.displayString());
    return result;
}

CTextList LogFormat::processMultiText(const LogItem &li) const
{
    CTextList result;
    result = CTextList(li.formatStringList());
    return result;
}

CTextList LogFormat::processXmlDocument(const LogItem &li) const
{
    CTextList result;
    Q_UNUSED(li); // TODO
    return result;
}

CTextList LogFormat::processSqlRecord(const LogItem &li) const
{
    CTextList result;
    Q_UNUSED(li); // TODO
    return result;
}
