#include "EfpFrameProcessor.h"

#include <Log.h>
#include <DetectorResultList.h>
#include <ObjdetFrontal.h>

EfpFrameProcessor::EfpFrameProcessor(QObject *parent)
    : QObject{parent}
    , mpFrontal(new ObjdetFrontal(this))
{
    setObjectName("EfpFrameProcessor");
}

void EfpFrameProcessor::initialize()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;

    emit initialized();
}

void EfpFrameProcessor::setup()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpFrontal);
    mpFrontal->loadDetectorXml("../detect/haarcascade_frontalface_default.xml");
    emit initialized();
}

void EfpFrameProcessor::start()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpFrontal);
    mRaw.neighbors(2), mRaw.set(ObjdetRawArguments::ForceRaw);
    mpFrontal->set(mRaw); // TODO
    emit initialized();
}

void EfpFrameProcessor::process(const QImage &qimg)
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;
    Q_CHECK_PTR(mpFrontal);
    mpFrontal->inputImage(qimg);
    mpFrontal->processCascadeClassifier();
    const QImage cDetImg = mpFrontal->detectImage(500); // TODO
    const DetectorResultList cDRL = mpFrontal->resultList();
    emit processed(cDetImg, cDRL);
}
