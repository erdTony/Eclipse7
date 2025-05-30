#include "FrontalObjdet.h"

#include "Objdet.h"

FrontalObjdet::FrontalObjdet(QObject *parent)
    : BaseObjdetEngine{Objdet::FaceFrontal, parent}
{
    setObjectName("FrontalObjdet");
}
