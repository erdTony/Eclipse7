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
    explicit LogOutText(const bool openStd=true,
                        const bool oneLine=false,
                        QObject *parent = nullptr);
    explicit LogOutText(const LogFileInfo &lfi,
                        const bool oneLine=false,
                        QObject *parent = nullptr);

public slots:
    virtual void start() override;
    virtual void write(const LogItem &li) override;
    virtual void write(const CTextList &ctxl) override;
    void open(const LogFileInfo &lfi);
    void openStdio();
    void close();

signals:

public: // const


public: // non-const
    void write(const AText &at, const LogItem &li);


public: // pointer
    QFile * file();

private:

private:
    LogFileInfo mFileInfo;
    QUrl mUrl;
    QFile * mpFile=nullptr;
    QTextStream * mpInfoStream=nullptr;
    QTextStream * mpErrorStream=nullptr;

};

inline QFile *LogOutText::file() { Q_CHECK_PTR(mpFile); return mpFile; }

