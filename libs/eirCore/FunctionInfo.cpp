#include "FunctionInfo.h"

#include <utility>

#include <QList>

class FunctionInfoData : public QSharedData
{
public:
    AText           dString;
    CTextList       dReturnType;
    CTextList       dAnte;
    CTextList       dNamespaces;
    CText           dClassName;
    CText           dFunctionName;
    QList<FunctionInfoArgument> dArgumentList;
    CTextList       dPost;
    int             dFuncInfoFlags;
};

FunctionInfo::FunctionInfo() : data(new FunctionInfoData) {;}
FunctionInfo::FunctionInfo(const AText &atx)  : data(new FunctionInfoData) { set(atx); }
FunctionInfo::FunctionInfo(const FunctionInfo &rhs) : data{rhs.data} {;}
FunctionInfo::FunctionInfo(FunctionInfo &&rhs) : data{std::move(rhs.data)} {;}
FunctionInfo::~FunctionInfo() {;}

FunctionInfo &FunctionInfo::operator=(const FunctionInfo &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

FunctionInfo &FunctionInfo::operator=(FunctionInfo &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

bool FunctionInfo::isNull() const
{
    Q_CHECK_PTR(data);
    return data->dString.isEmpty();
}

Count FunctionInfo::argCount() const
{
    Q_CHECK_PTR(data);
    return data->dArgumentList.count();
}

FunctionInfoArgument FunctionInfo::arg(const Index argix) const
{
    Q_CHECK_PTR(data);
    return (argix >= 0 && argix < Index(argCount()))
               ? data->dArgumentList.at(argix)
               : FunctionInfoArgument();
}

void FunctionInfo::set(const AText &atx)
{
    // TODO
    Q_UNUSED(atx);
}
