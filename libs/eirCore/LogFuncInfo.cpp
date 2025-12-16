#include "LogFuncInfo.h"

#include <utility>

#include <CText.h>
#include <CTextList.h>
#include <Types.h>

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

LogFuncInfo::LogFuncInfo(const AText &qfi) : data(new LogFuncInfoData) { set(qfi); }

CText LogFuncInfo::className() const
{
    Q_CHECK_PTR(data);
    return data->d_ClassName;
}

CText LogFuncInfo::functionName() const
{
    Q_CHECK_PTR(data);
    return data->d_FunctionName;
}

AText LogFuncInfo::qFuncInfo() const
{
    Q_CHECK_PTR(data);
    return data->d_QFuncInfo;
}

bool LogFuncInfo::operator ==(const LogFuncInfo &rhs) const
{
    return (data ? data->d_QFuncInfo : AText())
            == (rhs.data ? rhs.data->d_QFuncInfo : AText());
}

bool LogFuncInfo::operator !=(const LogFuncInfo &rhs) const
{
    return (data ? data->d_QFuncInfo : AText())
            != (rhs.data ? rhs.data->d_QFuncInfo : AText());
}

void LogFuncInfo::set(const AText &qfi)
{
    Q_CHECK_PTR(data);
    data->d_QFuncInfo = qfi;
    const Index ixLParen = qfi.indexOf('(');
    if (ixLParen > 1)
    {
        AText tLeftOfParen = qfi.first(ixLParen - 1);
        const Index ixLastSpace = tLeftOfParen.lastIndexOf(' ');
        if (ixLastSpace > 0)
        {
            data->d_AnteItems = tLeftOfParen
                .first(ixLastSpace - 1).simplified().split(' ');
            tLeftOfParen = tLeftOfParen.mid(ixLastSpace + 1);
        }
        const Index ixLastDColon = tLeftOfParen.lastIndexOf("::");
        if (ixLastDColon < 0
                || ixLastDColon > tLeftOfParen.length() - 2)
        {
            data->d_FunctionName = tLeftOfParen;
            data->d_ClassName.clear();
        }
        else
        {
            data->d_FunctionName = tLeftOfParen.mid(ixLastDColon + 2);
            data->d_ClassName = tLeftOfParen.left(ixLastDColon);
        }
    }
    // TODO Right of First Paren
}

//---------------------- QSharedDataPointer -----------------------
LogFuncInfo::LogFuncInfo() : data(new LogFuncInfoData) {;}
LogFuncInfo::LogFuncInfo(const LogFuncInfo &rhs) : data{rhs.data} {;}
LogFuncInfo::LogFuncInfo(LogFuncInfo &&rother) : data{std::move(rother.data)} {;}
LogFuncInfo::~LogFuncInfo() {;}

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


