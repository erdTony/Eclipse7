#pragma once
#include "eirLogger.h"

#include <QObject>

#include <QUrl>

#include "LogItem.h"

class EIRLOGGER_EXPORT AbstractLogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit AbstractLogOutput(QObject *parent = nullptr);
    explicit AbstractLogOutput(const QUrl &url, QObject *parent = nullptr);

public slots:
    void start(const QUrl &url);
    virtual void start() = 0;
    virtual void writeLine(const LogItem li) = 0;

signals:
    void starting(const QUrl &url);

public: // const


public: // const


public: // const

protected:
    QUrl mUrl;

};
