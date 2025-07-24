#include "LogFuncInfo.h"

#include <utility>

#include <CText.h>
#include <CTextList.h>

class LogFuncInfoData : public QSharedData
{
public:
    CTextList d_AnteItems;
    CText d_ReturnType;
    CTextList d_Namespaces;
    CText d_ClassName;
    CText d_FunctionName;
    CTextList d_ArgTypeNames;
    CTextList d_ArgValueNames;
    CTextList d_PostItems;
    AText d_QFuncInfo;
};

LogFuncInfo::LogFuncInfo()
    : data(new LogFuncInfoData)
{}

LogFuncInfo::LogFuncInfo(const LogFuncInfo &rhs)
    : data{rhs.data}
{}

LogFuncInfo::LogFuncInfo(LogFuncInfo &&rhs)
    : data{std::move(rhs.data)}
{}

LogFuncInfo &LogFuncInfo::operator=(const LogFuncInfo &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

LogFuncInfo &LogFuncInfo::operator=(LogFuncInfo &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

LogFuncInfo::~LogFuncInfo() {}
