#include "ImageAcqProperties.h"

#include <utility>

class ImageAcqPropertiesData : public QSharedData
{
public:
};

ImageAcqProperties::ImageAcqProperties()
    : data(new ImageAcqPropertiesData)
{}

ImageAcqProperties::ImageAcqProperties(const ImageAcqProperties &rhs)
    : data{rhs.data}
{}

ImageAcqProperties::ImageAcqProperties(ImageAcqProperties &&rhs)
    : data{std::move(rhs.data)}
{}

ImageAcqProperties &ImageAcqProperties::operator=(const ImageAcqProperties &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

ImageAcqProperties &ImageAcqProperties::operator=(ImageAcqProperties &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

ImageAcqProperties::~ImageAcqProperties() {}
