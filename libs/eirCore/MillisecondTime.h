#pragma once
#include "eirCore.h"

#include <QtGlobal>
#include <QDateTime>

#include "Types.h"

class EIRCORE_EXPORT MillisecondTime
{
public: // ctors
    MillisecondTime(void);
    MillisecondTime(MilliSeconds ems);
    MillisecondTime(const QDateTime & dt);

public: // const
    bool isNull(void) const;
    bool isBaseNull(void) const;
    bool isValid(void) const;
    MillisecondTime delta(MillisecondTime ems=current()) const;
    QDateTime toDateTime(void) const;
    QString toSecString(const MilliSeconds roll=1500) const;
    QString toString(const QString & format=QString()) const;
    QString timeString(const bool msec=false) const;
    operator MilliSeconds(void) const;

public: // non-const
    void set(const MillisecondTime other);
    MillisecondTime & operator += (const MillisecondTime d);
    MillisecondTime & operator -= (const MillisecondTime d);
    void nullify(void);

public: // static
    static MilliSeconds base(void);
    static MillisecondTime null(void);
    static MillisecondTime deltaBase(MillisecondTime ems=current());
    static QString baseString(const QString & format=QString());
    static MillisecondTime current(void);
    static MillisecondTime fromIso(const QString & isoDateTime);
    static MillisecondTime fromString(const QString & dateTime);

private:
    MilliSeconds mEpochMS;
    static const QDateTime smBaseDateTime;
    static const MillisecondTime smBaseMST;
    static const MillisecondTime smNullMST;
};

