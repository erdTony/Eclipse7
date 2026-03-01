#pragma once
#include "eirCore.h"

#include <QRgb>

#include <RationalColorList.h>

#include "Color.h"

class EIRCORE_EXPORT AnyColor
{
public: // types
    typedef QList<AnyColor> List;

public: // ctors
    AnyColor();
    AnyColor(const QString &aString);

public: // const
    BYTE byte(const Color::Component cc) const;
    QRgb qrgba32() const;


public: // non-const
    void set(const QString &aString);
    void set(const Color::Component cc, const WORDF wfv);

private:
    QString mColorName;
    RationalColorList mComponentValueList;
};
