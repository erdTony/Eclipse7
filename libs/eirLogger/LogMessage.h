#pragma once
#include "eirLogger.h"

#include <QtDebug>

#include "LogItem.h"

class EIRLOGGER_EXPORT LogMessage
{
public: // ctors
    LogMessage();
    LogMessage(QtMsgType type,
                const QMessageLogContext &context,
                const QString &msg);

public: // const
    QString message() const;
    LogItem item() const;

public: // non-const
    void set(const QString &msg);


public: // const

private:
    QtMsgType mQtMsgType;
    QMessageLogContext mContext;
    QString mMessage;
    LogItem mItem;
};

inline QString LogMessage::message() const { return mMessage; }
    inline LogItem LogMessage::item() const { return mItem; }
