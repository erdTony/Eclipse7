#pragma once

#include <QSharedDataPointer>

#include <QList>

class ObjdetResultData;

class ObjdetResult
{
public: // types
    typedef QList<ObjdetResult> List;

public: // our ctors

public: // const
    qreal distance() const { return 0.0; } // TODO

public: // non-const

    // SharedData
public:
    ObjdetResult();
    ObjdetResult(const ObjdetResult &);
    ObjdetResult &operator=(const ObjdetResult &);
    ~ObjdetResult();
private:
    QSharedDataPointer<ObjdetResultData> data;
};
