#pragma once
#include "eirLogger.h"

#include <QByteArray>
#include <QVariantList>

#include <AText.h>
#include <Types.h>

#include "LogCondition.h"
#include "LogLevel.h"
//#include "LogObject.h"

class EIRLOGGER_EXPORT LogEntry
{
public: // ctors
    LogEntry();
    LogEntry(const LogLevel::Value level,
             const AText &message);
    LogEntry(const LogLevel::Value level,
             const AText &format,
             const QVariantList &args);
    LogEntry(const LogLevel::Value level,
             const LogCondition cond,
             const QVariantList &args);

public: // const
    LogLevel level() const;
    AText text() const;
    LogCondition condition() const;
    QVariantList arguments() const;
    QVariant argument(const Index ix) const;
    QByteArray xport() const;


public: // non-const
    void mport(const QByteArray &ba);


public: // pointers

private:
    LogLevel::Value mLevel=LogLevel::$nullLevel;
    Milliseconds mEntryMsec;
    AText mText;
    LogCondition mCondition;
    QVariantList mArguments;
};

//extern EIRLOGGER_EXPORT QDebug operator << (QDebug dbg, const LogEntry &le);


inline LogLevel LogEntry::level() const { return mLevel; }
inline AText LogEntry::text() const { return mText; }
inline LogCondition LogEntry::condition() const { return mCondition; }
inline QVariantList LogEntry::arguments() const { return mArguments; }
