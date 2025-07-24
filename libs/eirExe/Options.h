#pragma once

#include <QObject>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QMap>

#include <CText.h>

class Options : public QObject
{
    Q_OBJECT
public: // typedef
    typedef QPair<CText, QString> Positional;

public: // ctors
    explicit Options(QObject *parent = nullptr);

public slots:
    void add(const QCommandLineOption opt);
    void add(const CText &name, const QString &desc);
    void addHelp();
    void addVersion();
    void setup();
    void execute();

signals:
    void added(const QCommandLineOption opt);
    void added(const CText &name);



public: // const



public: // non-const


public: // pointers
    QCommandLineParser & parser();


private:
    QCommandLineParser mParser;
    QMap<CText, QCommandLineOption> mKeyOptionMap;
    QList<Positional> mPositionalList;

};

inline QCommandLineParser &Options::parser() { return mParser; }
