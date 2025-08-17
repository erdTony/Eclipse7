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

public slots:
    virtual void start() = 0;
    virtual void writeLine(const LogItem li) = 0;

signals:

public: // const


public: // const


public: // const

protected:

};
