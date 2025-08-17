#pragma once
#include "eirBase.h"

#include <QtGlobal>
#include <QDateTime>

#include "Types.h"

class EIRBASE_EXPORT MillisecondTime
{
public: // ctors
    MillisecondTime(void);
    MillisecondTime(Milliseconds ems);
    MillisecondTime(const QDateTime & dt);

public: // const
    bool isNull(void) const;
    bool isBaseNull(void) const;
    bool isValid(void) const;
    MillisecondTime delta(MillisecondTime ems=current()) const;
    QDateTime toDateTime(void) const;
    QString toString(const QString & format=QString()) const;
    QString timeString(const bool msec=false) const;
    operator Milliseconds(void) const;

public: // non-const
    void set(const MillisecondTime other);
    MillisecondTime & operator += (const MillisecondTime d);
    MillisecondTime & operator -= (const MillisecondTime d);
    void nullify(void);

public: // static
    static Milliseconds base(void);
    static MillisecondTime null(void);
    static MillisecondTime deltaBase(MillisecondTime ems=current());
    static QString baseString(const QString & format=QString());
    static MillisecondTime current(void);
    static MillisecondTime fromIso(const QString & isoDateTime);
    static MillisecondTime fromString(const QString & dateTime);

private:
    Milliseconds mEpochMS;
    static const QDateTime smBaseDateTime;
    static const MillisecondTime smBaseMST;
    static const MillisecondTime smNullMST;
};

