#pragma once

#include <QObject>

#include <ObjdetRawArguments.h>
class DetectorResultList;
class ObjdetFrontal;

class EfpFrameProcessor : public QObject
{
    Q_OBJECT
public:
    explicit EfpFrameProcessor(QObject *parent = nullptr);

public slots:
    void initialize();
    void setup();
    void start();
    void process(const QImage &qimg);

signals:
    void initialized();
    void setupd();
    void started();
    void processed(const QImage &detectImage, const DetectorResultList &drl);

signals:

private:
    ObjdetFrontal * mpFrontal;
    ObjdetRawArguments mRaw;
};
