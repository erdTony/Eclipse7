#pragma once
#include "eirLogger.h"

#include <QObject>

#include <QUrl>

#include <CText.h>
class CTextList;

#include "LogFormat.h"
#include "LogItem.h"
#include "LogUrl.h"

class EIRLOGGER_EXPORT LogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit LogOutput(QObject *parent = nullptr);
public:
    LogOutput(const CText &url, QObject *parent = nullptr);

public slots:
    virtual void start(const CText &url);
    virtual void write(const LogItem &li);
    virtual void write(const CTextList &ctxl);
    virtual void flush();
    virtual void close();

signals:

public: // const
    CText name() const;
    LogUrl url() const;

public: // non-const


public: // pointers

protected:
    CText mName;
    LogUrl mUrl;
};

inline CText LogOutput::name() const { return mName; }
inline LogUrl LogOutput::url() const { return mUrl; }


