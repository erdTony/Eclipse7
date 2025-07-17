#pragma once

#include <QThread>

class ImageAcqManager;

class ImageAcqThread : public QThread
{
    Q_OBJECT
public:
    ImageAcqThread(ImageAcqManager *parent = nullptr);

private:

};
