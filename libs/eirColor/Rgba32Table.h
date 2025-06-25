#pragma once
#include "eirColor.h"

#include <QList>
#include <QRgb>

class AnyColorTable;

class EIRCOLOR_EXPORT Rgba32Table
{
public:
    Rgba32Table();
    Rgba32Table(const AnyColorTable &aTable);

public: // non-const
    void set(const AnyColorTable &aTable);

private:
    QList<QRgb> mRgbaList;
};
