#pragma once

#include <QSharedDataPointer>

class ImageAcqPropertiesData;

class ImageAcqProperties
{
public:
    ImageAcqProperties();
    ImageAcqProperties(const ImageAcqProperties &);
    ImageAcqProperties(ImageAcqProperties &&);
    ImageAcqProperties &operator=(const ImageAcqProperties &);
    ImageAcqProperties &operator=(ImageAcqProperties &&);
    ~ImageAcqProperties();

private:
    QSharedDataPointer<ImageAcqPropertiesData> data;
};
