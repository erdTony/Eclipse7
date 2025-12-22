#pragma once

#include <QSharedDataPointer>

class FunctionInfoArgumentData;

class FunctionInfoArgument
{
public:
    FunctionInfoArgument();
    FunctionInfoArgument(const FunctionInfoArgument &);
    FunctionInfoArgument(FunctionInfoArgument &&);
    ~FunctionInfoArgument();
    FunctionInfoArgument &operator=(const FunctionInfoArgument &);
    FunctionInfoArgument &operator=(FunctionInfoArgument &&);

private:
    QSharedDataPointer<FunctionInfoArgumentData> data;
};
