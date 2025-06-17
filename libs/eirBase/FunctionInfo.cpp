#include "FunctionInfo.h"

#include <utility>

class FunctionInfoData : public QSharedData
{
public:
};

FunctionInfo::FunctionInfo()
    : data(new FunctionInfoData)
{}

FunctionInfo::FunctionInfo(const FunctionInfo &rhs)
    : data{rhs.data}
{}

FunctionInfo::FunctionInfo(FunctionInfo &&rhs)
    : data{std::move(rhs.data)}
{}

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

FunctionInfo::~FunctionInfo() {}
