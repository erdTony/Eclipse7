#pragma once
#include "eirCore.h"

#include <QtDebug>

#include "LogItem.h"

class EIRCORE_EXPORT LogMessage
{
public: // ctors
    LogMessage();
    LogMessage(QtMsgType type,
                const QMessageLogContext &context,
                const QString &msg);

public: // const
    bool isNull() const;
    QtMsgType qMsgType() const;
    QString fileName() const;
    int fileLine() const;
    QString funcName() const;
    QString message() const;

public: // non-const

public:

private:
    QtMsgType mQtMsgType=QtMsgType(-1);
    QString mFileName;
    QString mFuncName;
    int mFileLine=-1;
    QString mMessage;
};

inline QtMsgType LogMessage::qMsgType() const { return mQtMsgType; }
inline QString LogMessage::fileName() const { return mFileName; }
inline int LogMessage::fileLine() const { return mFileLine; }
inline QString LogMessage::funcName() const { return mFuncName; }
inline QString LogMessage::message() const { return mMessage; }
