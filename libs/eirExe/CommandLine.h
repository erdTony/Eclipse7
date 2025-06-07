#pragma once

#include <QObject>

#include <QCommandLineOption>

class CommandLine : public QObject
{
    Q_OBJECT
public:

public: // ctors
    explicit CommandLine(QObject *parent = nullptr);

public slots:
    void add(const QCommandLineOption opt);

signals:
    void added(const QCommandLineOption opt);

public: // const


public: // non-const


public: // pointers


private:

signals:
};
