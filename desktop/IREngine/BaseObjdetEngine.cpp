#include "BaseObjdetEngine.h"

#include "ObjectHelper.h"

BaseObjdetEngine::BaseObjdetEngine(QObject *parent)
    : Objdet{parent}
{
    setObjectName("BaseObjdetEngine:Null");
}

BaseObjdetEngine::BaseObjdetEngine(const Objdet::Class objcls, QObject *parent)
    : Objdet{objcls, parent}
{
    setObjectName("BaseObjdetEngine:" + className(objcls));
}

