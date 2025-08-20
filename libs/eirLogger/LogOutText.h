#pragma once
#include "eirLogger.h"

#include <QObject>
#include "LogOutput.h"

class QFile;
class QTextStream;

class LogFileInfo;


class EIRLOGGER_EXPORT LogOutText : public LogOutput
{
    Q_OBJECT
public:
    explicit LogOutText(const bool openStd=true, QObject *parent = nullptr);
    explicit LogOutText(const LogFileInfo &lfi, QObject *parent = nullptr);

public slots:
    virtual void start() override;
    virtual void write(const LogItem &li) override;
    void open(const LogFileInfo &lfi);
    void openStdio();
    void close();

signals:

public: // const


public: // non-const
    void write(const AText &at, const LogItem &li);


public: // pointer

private:

private:
    LogFileInfo mFileInfo;
    QUrl mUrl;
    QFile * mpFile=nullptr;
    QTextStream * mpInfoStream=nullptr;
    QTextStream * mpErrorStream=nullptr;

};
