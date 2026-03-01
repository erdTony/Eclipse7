#pragma once
#include "eirCore.h"

#include <QList>
#include <QRgb>

class AnyColorTable;

class EIRCORE_EXPORT Rgba32Table
{
public: // types
    typedef QList<QRgb> RgbList;

public:
    Rgba32Table();
    Rgba32Table(const AnyColorTable &aTable);

public: // const
    bool isEmpty() const;

public: // non-const
    void set(const AnyColorTable &aTable);


public: // static
    static RgbList greyTable(const qreal opacity=1.0);

private:
    RgbList mRgbaList;
    static RgbList smGreyTable;
};

inline bool Rgba32Table::isEmpty() const { return mRgbaList.isEmpty(); }
