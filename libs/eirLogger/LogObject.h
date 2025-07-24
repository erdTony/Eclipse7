#pragma once

#include <QObject>
#include <QtLogging>

#include <ATextList.h>
#include <Types.h>

class Log : public QObject
{
    Q_OBJECT
public: // types
    enum Level
    {
        $nullLevel = 0,         //  0
        Troll,                  //  1
        Minimum,                //  2
        TDetail,                //  3
        Detail,                 //  4
        FnArg,                  //  5
        FnExit,                 //  6
        FnEnter,                //  7
        TInfo,                  //  8
        Info,                   //  9
        TDump,                  // 10
        Trace,                  // 11
        TPrefer,                // 12
        Level13,                // 13
        Level14,                // 14
        Level15,                // 15
        Level16,                // 16
        Level17,                // 17
        TWarning,               // 18
        Warning,                // 19
        Level20,                // 20
        Level21,                // 21
        Level22,                // 22
        Expect,                 // 23
        Assert,                 // 24
        LogManage,              // 25
        TError,                 // 26
        Error,                  // 27
        Abort,                  // 28
        Memory,                 // 29
        Shutdown,               // 30
        Network                 // 31
    };

    enum FlagLevel
    {
        $nullFlag               = 0,
        Flag$null               = 1 << $nullLevel,
        FlagTroll               = 1 << Troll,
        FlagMinimum             = 1 << Minimum,
        FlagTDetail             = 1 << TDetail,
        FlagDetail              = 1 << Detail,
        FlagFnArg               = 1 << FnArg,
        FlagFnExit              = 1 << FnExit,
        FlagFnEnter             = 1 << FnEnter,
        FlagTInfo               = 1 << TInfo,
        FlagInfo                = 1 << Info,
        FlagTDump               = 1 << TDump,
        FlagTrace               = 1 << Trace,
        FlagTPrefer             = 1 << TPrefer,
        FlagLevel13             = 1 << Level13,
        FlagLevel14             = 1 << Level14,
        FlagLevel15             = 1 << Level15,
        FlagLevel16             = 1 << Level16,
        FlagLevel17             = 1 << Level17,
        FlagTWarning            = 1 << TWarning,
        FlagWarning             = 1 << Warning,
        FlagLevel20             = 1 << Level20,
        FlagLevel21             = 1 << Level21,
        FlagLevel22             = 1 << Level22,
        FlagExpect              = 1 << Expect,
        FlagAssert              = 1 << Assert,
        FlagLogManage           = 1 << LogManage,
        FlagTError              = 1 << TError,
        FlagError               = 1 << Error,
        FlagAbort               = 1 << Abort,
        FlagMemory              = 1 << Memory,
        FlagShutdown            = 1 << Shutdown,
        FlagNetwork             = 1 << Network,
    };
    Q_DECLARE_FLAGS(LevelMask, FlagLevel)
    Q_FLAG(LevelMask)

    enum Operation
    {
        $nullOperation = 0,
        Less,
    };

    enum MsgType
    {
        $nullMsgType    = 0,
        InfoType,
        TraceType,
        WarnType,
        ErrorType,
        AbortType,
        $fallback       = WarnType
    };

public: // ctors
    explicit Log(QObject *parent = nullptr);

public slots:
    void start();
    void captureTroll();
    void releaseTroll();

signals:

public: // const

public: // non-const

public: // static
    static MsgType msgType(const AText &at);
    static MsgType msgType(const Level lvl);
    static QtMsgType qMsgType(const MsgType mt);

public: // pointers

private:
    QtMessageHandler mOldHandler=nullptr;
    static ATextList smPatternList;
};

extern void capturedTrollHandler(QtMsgType type,
                                 const QMessageLogContext &context,
                                 const QString &message);
