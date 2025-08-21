#pragma once
#include "eirLogger.h"

#include <QObject>

#include <QUrl>

class CTextList;

#include "LogFormat.h"
#include "LogItem.h"

class EIRLOGGER_EXPORT LogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit LogOutput(const CText &name,
                       const LogFormat::Format fmtv,
                       QObject *parent = nullptr);

public slots:
    virtual void start() = 0;
    virtual void write(const LogItem &li) = 0;
    virtual void write(const CTextList &ctxl) = 0;

signals:

public: // const
    CText name() const;
    LogFormat format() const;

public: // non-const


public: // pointers

protected:
    CText mName;
    LogFormat mFormat;

};

inline CText LogOutput::name() const { return mName; }
inline LogFormat LogOutput::format() const { return mFormat; }


