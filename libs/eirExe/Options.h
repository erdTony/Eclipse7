#pragma once

#include <QObject>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QMap>

#include <KeySeg.h>

class Options : public QObject
{
    Q_OBJECT
public: // typedef

public: // ctors
    explicit Options(QObject *parent = nullptr);

public slots:
    void add(const QCommandLineOption opt);

signals:
    void added(const QCommandLineOption opt);



public: // const


public: // non-const


public: // pointers


private:
    QCommandLineParser mParser;
    QMap<KeySeg, QCommandLineOption> mKeyOptionMap;

};
