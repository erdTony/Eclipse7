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
    void setup();
    void execute();

signals:

public: // const


public: // non-const


public: // pointers


private:

signals:
};
