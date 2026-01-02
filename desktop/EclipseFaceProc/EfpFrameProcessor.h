#pragma once

#include <QObject>

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

signals:
    void initialized();
    void setupd();
    void started();

signals:

private:
    ObjdetFrontal * mpFrontal;
};
