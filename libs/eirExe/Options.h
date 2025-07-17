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
    typedef QPair<KeySeg, QString> Positional;

public: // ctors
    explicit Options(QObject *parent = nullptr);

public slots:
    void add(const QCommandLineOption opt);
    void add(const KeySeg &name, const QString &desc);
    void addHelp();
    void addVersion();
    void setup();
    void execute();

signals:
    void added(const QCommandLineOption opt);
    void added(const KeySeg &name);



public: // const



public: // non-const


public: // pointers
    QCommandLineParser & parser();


private:
    QCommandLineParser mParser;
    QMap<KeySeg, QCommandLineOption> mKeyOptionMap;
    QList<Positional> mPositionalList;

};

inline QCommandLineParser &Options::parser() { return mParser; }
