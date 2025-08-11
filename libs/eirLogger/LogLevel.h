#pragma once
#include "eirLogger.h"

#include <CText.h>


class EIRLOGGER_EXPORT LogLevel
{
public: // types
    enum Value : quint8
    {
        $nullLevel          = 0,
        Minimum             = 1,
        FnArgVal            = 2,
        FnArgName           = 3,
        FnReturn            = 4,
        FnExit              = 5,
        FnEnter             = 6,
        TTrivia             = 7,
        UTrivia             = 8,
        TDetail             = 9,
        UDetail             = 10,
        DumpVal             = 11,
        Dump                = 12,
        Trace               = 13,
        TInfo               = 14,
        UInfo               = 15,
        TPrefer             = 16,
        UPrefer             = 17,
        TProgress           = 18,
        UProgress           = 19,
        $minWarning         = 20,
        TWarning            = 21,
        UWarning            = 22,
        $minCritical        = 23,
        Error               = 24,
        Expect              = 25,
        Memory              = 26,
        Assert              = 27,
        Shutdown            = 28,
        Maximum             = 31,
    };

    enum Flag
    {
        $nullLevelFlag      = 0,
        MinimumFlag         = 1 << Minimum,
        FnArgValFlag        = 1 << FnArgVal,
        FnArgNameFlag       = 1 << FnArgName,
        FnReturnFlag        = 1 << FnReturn,
        FnExitFlag          = 1 << FnExit,
        FnEnterFlag         = 1 << FnEnter,
        TTriviaFlag         = 1 << TTrivia,
        UTriviaFlag         = 1 << UTrivia,
        TDetailFlag         = 1 << TDetail,
        UDetailFlag         = 1 << UDetail,
        DumpValFlag         = 1 << DumpVal,
        DumpFlag            = 1 << Dump,
        TraceFlag           = 1 << Trace,
        TInfoFlag           = 1 << TInfo,
        UInfoFlag           = 1 << UInfo,
        TPreferFlag         = 1 << TPrefer,
        UPreferFlag         = 1 << UPrefer,
        TProgressFlag       = 1 << TProgress,
        UProgressFlag       = 1 << UProgress,
        TWarningFlag        = 1 << TWarning,
        UWarningFlag        = 1 << UWarning,
        ErrorFlag           = 1 << Error,
        ExpectFlag          = 1 << Expect,
        MemoryFlag          = 1 << Memory,
        AssertFlag          = 1 << Assert,
        ShutdownFlag        = 1 << Shutdown,
        MaximumFlag         = 1 << Maximum
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
    LogLevel();
    LogLevel(const Value v);

public: // const
    Value value() const;
    CText name() const;
    Flag flag() const;

public: // non-const
    void set(const Value v);


public: // static
    static CText name(const Value v);
    static MsgType msgType(const CText &ct);
    static MsgType msgType(const LogLevel::Value lvl);
    static QtMsgType qMsgType(const MsgType mt);

private:
    Value mValue=$nullLevel;
    Flag mFlag=$nullLevelFlag;
};

inline LogLevel::Value LogLevel::value() const { return mValue; }
inline CText LogLevel::name() const { return name(value()); }
inline LogLevel::Flag LogLevel::flag() const { return mFlag; }
