#pragma once

#include <QSharedDataPointer>

class FunctionInfoData;

class FunctionInfo
{
public:
    FunctionInfo();
    FunctionInfo(const FunctionInfo &);
    FunctionInfo(FunctionInfo &&);
    FunctionInfo &operator=(const FunctionInfo &);
    FunctionInfo &operator=(FunctionInfo &&);
    ~FunctionInfo();

private:
    QSharedDataPointer<FunctionInfoData> data;
};
