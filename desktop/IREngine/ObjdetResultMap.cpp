#include "ObjdetResultMap.h"

ObjdetResultMap::ObjdetResultMap() {;}

void ObjdetResultMap::insert(const ObjdetResult &res)
{
    qreal tDist = res.distance();
    insert(tDist, res);
}

void ObjdetResultMap::insert(const qreal dist, const ObjdetResult &res)
{
    mMap.insert(dist, res);
}
