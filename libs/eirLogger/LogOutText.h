#pragma once
#include "eirLogger.h"

#include <QObject>
#include "AbstractLogOutput.h"

class QFile;
class QTextStream;

class LogFileInfo;


class EIRLOGGER_EXPORT LogOutText : public AbstractLogOutput
{
    Q_OBJECT
public:
    explicit LogOutText(const bool openStd=true, QObject *parent = nullptr);
    explicit LogOutText(const LogFileInfo &url, QObject *parent = nullptr);

public slots:
    virtual void start() override;
    virtual void writeLine(const LogItem li) override;
    void open(const LogFileInfo &fi);
    void openStdio();
    void close();

signals:

public: // const


public: // non-const
    void writeLine(const AText &at, const LogItem &li);


public: // pointer

private:

private:
    LogFileInfo mFileInfo;
    QUrl mUrl;
    QFile * mpFile=nullptr;
    QTextStream * mpInfoStream=nullptr;
    QTextStream * mpErrorStream=nullptr;

};
