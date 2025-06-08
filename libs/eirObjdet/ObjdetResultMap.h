#pragma once

#include <QMultiMap>
#include "ObjdetResult.h"

class ObjdetResultMap
{
public: // ctors
    ObjdetResultMap();

public: // const
    ObjdetResult::List list() const;

public: // non-const
    void insert(const ObjdetResult &res);
    void insert(const qreal dist, const ObjdetResult &res);


private:
    QMultiMap<qreal, ObjdetResult> mMap;
};
