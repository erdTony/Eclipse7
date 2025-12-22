#include "FunctionInfoArgument.h"

#include <utility>

#include <QList>
#include <QVariant>

#include "AText.h"
#include "CText.h"
#include "CTextList.h"
#include "FunctionInfoArgument.h"

class FunctionInfoArgumentData : public QSharedData
{
public:
    CTextList       dType;
    CText           dName;
    QVariant        dVariant;
    AText           dDefaltValue;
    int             dFuncInfoFlags;
};

FunctionInfoArgument::FunctionInfoArgument() : data(new FunctionInfoArgumentData) {;}
FunctionInfoArgument::FunctionInfoArgument(const FunctionInfoArgument &rhs) : data{rhs.data} {;}
FunctionInfoArgument::FunctionInfoArgument(FunctionInfoArgument &&rhs) : data{std::move(rhs.data)} {;}
FunctionInfoArgument::~FunctionInfoArgument() {}

FunctionInfoArgument &FunctionInfoArgument::operator=(const FunctionInfoArgument &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

FunctionInfoArgument &FunctionInfoArgument::operator=(FunctionInfoArgument &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

