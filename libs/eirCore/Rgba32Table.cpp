#include "Rgba32Table.h"

#include <Types.h>

#include "AnyColorTable.h"

Rgba32Table::RgbList Rgba32Table::smGreyTable;

Rgba32Table::Rgba32Table() {;}
Rgba32Table::Rgba32Table(const AnyColorTable &aTable) { set(aTable); }

void Rgba32Table::set(const AnyColorTable &aTable)
{
    mRgbaList.clear();
    foreach (const AnyColor cAny, aTable.list())
    {
        const QRgb cRgba = cAny.qrgba32();
        mRgbaList.append(cRgba);
    }
}

Rgba32Table::RgbList Rgba32Table::greyTable(const qreal opacity)
{
    const int cAlpha = qRound(opacity * 255.0);
    if (smGreyTable.isEmpty())
    {
        smGreyTable = RgbList(256);
        for (int ix = 0; ix < 256; ++ix)
            smGreyTable[ix] = qRgba(ix, ix, ix, cAlpha);
    }
    return smGreyTable;
}

