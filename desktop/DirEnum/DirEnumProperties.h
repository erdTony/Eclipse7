#pragma once

#include <QSharedDataPointer>

class DirEnumPropertiesData;

class DirEnumProperties
{
public:
    DirEnumProperties();
    DirEnumProperties(const DirEnumProperties &);
    DirEnumProperties(DirEnumProperties &&);
    DirEnumProperties &operator=(const DirEnumProperties &);
    DirEnumProperties &operator=(DirEnumProperties &&);
    ~DirEnumProperties();

private:
    QSharedDataPointer<DirEnumPropertiesData> data;
};
