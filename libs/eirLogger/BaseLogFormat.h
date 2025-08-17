#pragma once

#include <QVariant>

#include "LogItem.h"

class BaseLogFormat : public QVariant
{
public:
    BaseLogFormat();
    BaseLogFormat(const LogItem &li);

public: // const
    QString string() const;
    QStringList stringList() const;


public: // non-const
    void set(const LogItem &li);

public: // pointers
    BaseLogFormat it() const;
    BaseLogFormat & it();

private:
    LogItem li() const;

private:
    LogItem mLogItem;
};

inline void BaseLogFormat::set(const LogItem &li) { mLogItem = li; }
inline LogItem BaseLogFormat::li() const { return mLogItem; }
