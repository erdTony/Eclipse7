#pragma once
#include "eirLogger.h"

#include <QByteArray>
#include <QVariantList>

#include <AText.h>
#include <CText.h>
#include <Types.h>
#include <Uid.h>

#include "LogCondition.h"
#include "LogLevel.h"
//#include "LogObject.h"

class EIRLOGGER_EXPORT LogEntry
{
public: // ctors
    LogEntry();
    LogEntry(const QByteArray &ba);
    LogEntry(const LogLevel::Value level,
             const AText &message);
    LogEntry(const LogLevel::Value level,
             const AText &format,
             const QVariant &arg1,
             const QVariant &arg2=QVariant(),
             const QVariant &arg3=QVariant(),
             const QVariant &arg4=QVariant()); // TODO argTypeNames???
    LogEntry(const LogLevel::Value level,
             const AText &format,
             const QVariantList &args); // TODO argNames???
    LogEntry(const LogLevel::Value level,
             const LogCondition cond,
             const CText &expName,
             const QVariant &expValue,
             const CText &actName=CText(),
             const QVariant &actValue=QVariant());

public: // const
    bool isNull() const;
    LogLevel level() const;
    Milliseconds logMsec() const;
    Uid logUid() const;
    AText text() const;
    LogCondition condition() const;
    CText expectedName() const;
    CText actualName() const;
    QVariantList arguments() const;
    QVariant argument(const Index ix) const;
    QByteArray xport() const;


public: // non-const
    void mport(const QByteArray &ba);


public: // pointers

private:
    LogLevel mLevel;
    Milliseconds mLogMsec;
    Uid mLogUid;
    AText mText;
    LogCondition mCondition;
    CText mExpectedName;
    CText mActualName;
    QVariantList mArguments;
};

//extern EIRLOGGER_EXPORT QDebug operator << (QDebug dbg, const LogEntry &le);


inline LogLevel LogEntry::level() const { return mLevel; }
inline Milliseconds LogEntry::logMsec() const { return mLogMsec; }
inline Uid LogEntry::logUid() const { return mLogUid; }
inline AText LogEntry::text() const { return mText; }
inline LogCondition LogEntry::condition() const { return mCondition; }
inline CText LogEntry::expectedName() const { return mExpectedName; }
inline CText LogEntry::actualName() const { return mActualName; }
inline QVariantList LogEntry::arguments() const { return mArguments; }
