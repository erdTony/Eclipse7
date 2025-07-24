#include "DirEnumProperties.h"

#include <utility>

class DirEnumPropertiesData : public QSharedData
{
public:
};

DirEnumProperties::DirEnumProperties()
    : data(new DirEnumPropertiesData)
{}

DirEnumProperties::DirEnumProperties(const DirEnumProperties &rhs)
    : data{rhs.data}
{}

DirEnumProperties::DirEnumProperties(DirEnumProperties &&rhs)
    : data{std::move(rhs.data)}
{}

DirEnumProperties &DirEnumProperties::operator=(const DirEnumProperties &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

DirEnumProperties &DirEnumProperties::operator=(DirEnumProperties &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

DirEnumProperties::~DirEnumProperties() {}
