#pragma once
#include "eirLogger.h"

#include <QObject>

#include <QUrl>

#include <CText.h>
class CTextList;

//#include "LogFormat.h"
//#include "LogItem.h"
#include "LogUrl.h"
class LogItem;

class EIRLOGGER_EXPORT BaseLogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit BaseLogOutput(QObject *parent = nullptr);
public:
    BaseLogOutput(const CText &url, QObject *parent = nullptr);

public slots:
    virtual void start() = 0;
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

inline CText BaseLogOutput::name() const { return mName; }
inline LogUrl BaseLogOutput::url() const { return mUrl; }


