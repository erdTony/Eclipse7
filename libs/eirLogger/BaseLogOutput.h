#pragma once

#include <QObject>

#include <QUrl>

#include "LogItem.h"

class BaseLogOutput : public QObject
{
    Q_OBJECT
protected:
    explicit BaseLogOutput(QObject *parent = nullptr);
    explicit BaseLogOutput(const QUrl &url, QObject *parent = nullptr);

public slots:
    virtual void start() = 0;
    void start(const QUrl &url);
    virtual void writeLine(const LogItem li) {;}

signals:
    void starting(const QUrl &url);

public: // const


public: // const


public: // const

protected:
    QUrl mUrl;

};
