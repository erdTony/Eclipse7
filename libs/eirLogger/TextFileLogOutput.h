#pragma once

#include <QObject>
#include "BaseLogOutput.h"

class QFile;
class QTextStream;

#include "LogContext.h"

class TextFileLogOutput : public BaseLogOutput
{
    Q_OBJECT
public:
    explicit TextFileLogOutput(QObject *parent = nullptr);
    explicit TextFileLogOutput(const QUrl &url, QObject *parent = nullptr);

public slots:
    virtual void start() override;
    virtual void writeLine(const LogItem li) override;
    void open(const FileInfo &fi);
    void openStdio();
    void close();

signals:

public: // const


public: // non-const
    void writeLine(const AText &at, const LogItem &li);


public: // pointer

private:
    AText contextLine();

private:
    QFile * mpFile=nullptr;
    QTextStream * mpInfoStream=nullptr;
    QTextStream * mpErrorStream=nullptr;
    LogContext mCurrentContext;

};
