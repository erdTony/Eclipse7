#include "BaseObjdetMarker.h"

BaseObjdetMarker::BaseObjdetMarker(QObject *parent)
    : QObject{parent}
{
    setObjectName("ObjdetMarker");
    reset();
}
