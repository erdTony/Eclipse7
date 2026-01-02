#include "EfpFrameProcessor.h"

#include <Log.h>
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

    emit initialized();
}

void EfpFrameProcessor::start()
{
    FNSLOT();
    qInfo() << Q_FUNC_INFO;

    emit initialized();
}
