#pragma once
#include "eirLogger.h"

#include <QObject>

#include <QUrl>

#include "LogFormat.h"
#include "LogItem.h"

class EIRLOGGER_EXPORT LogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit LogOutput(const CText &name,
                       const LogFormat::Format fmt,
                       QObject *parent = nullptr);

public slots:
    virtual void start() = 0;
    virtual void write(const LogItem &li) = 0;

signals:

public: // const
    CText name() const;

public: // non-const


public: // pointers

protected:
    CText mName;
    LogFormat mFormat;

};

inline CText LogOutput::name() const { return mName; }


