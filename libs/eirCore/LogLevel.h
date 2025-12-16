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
        FnArg               = 2,
        FnReturn            = 3,
        FnExit              = 4,
        FnEnter             = 5,
        Connect             = 6,
        TTrivia             = 7,
        UTrivia             = 8,
        TDetail             = 9,
        UDetail             = 10,
        DumpHex             = 11,
        DumpVal             = 12,
        Dump                = 13,
        Trace               = 14,
        TInfo               = 15,
        UInfo               = 16,
        TPrefer             = 17,
        UPrefer             = 18,
        TProgress           = 19,
        UProgress           = 20,
        Unused              = 21,
        TWarning            = 22,
        UWarning            = 23,
        $minError           = 24,
        Error               = 25,
        Expect              = 26,
        Memory              = 27,
        Assert              = 28,
        Shutdown            = 29,
        Maximum             = 30,
        $maxLevel           = 31,
    };

    enum Flag
    {
        $nullLevelFlag      = 0,
        MinimumFlag         = 1 << Minimum,
        FnArgFlag           = 1 << FnArg,
        FnReturnFlag        = 1 << FnReturn,
        FnExitFlag          = 1 << FnExit,
        FnEnterFlag         = 1 << FnEnter,
        ConnectFlag         = 1 << Connect,
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
        MaximumFlag         = 1 << Maximum,
    };
    Q_DECLARE_FLAGS(Flags, Flag);

    enum FlagMask
    {
        $nullMask           = 0,
        UserMask            = UTriviaFlag | UDetailFlag | UInfoFlag | UPreferFlag | UWarningFlag,
        FunctionMask        = FnArgFlag | FnReturnFlag | FnExitFlag | FnEnterFlag | ConnectFlag,
        TraceMask           = TTriviaFlag | TDetailFlag | TInfoFlag | TPreferFlag | TWarningFlag,
        ErrorMask           = ErrorFlag | ExpectFlag | MemoryFlag | AssertFlag | ShutdownFlag,
    };

    enum MsgType
    {
        $nullMsgType    = 0,
        InfoType,
        TraceType,
        WarnType,
        ErrorType,
        AbortType,
        $fallbackType       = WarnType
    };


public: // ctors
    LogLevel();
    LogLevel(const Value v);

public: // const
    Value value() const;
    bool isNull() const;
    CText name() const;
    Flag flag() const;
    char chr() const;
    MsgType msgType() const;
    bool isValidLevel() const;
    bool isWarn() const;
    bool isError() const;
    bool isFatal() const;

public: // non-const
    void set(const int i);
    void set(const Value v);


public: // static
    static bool isValidLevel(const int i);
    static CText name(const Value v);
    static CText name(const QtMsgType qmt);
    static MsgType msgType(const CText &ctx);
    static MsgType msgType(const LogLevel::Value lvl);
    static QtMsgType qMsgType(const MsgType mt);
    static FlagMask mask(const CText &ctx);
    static void fatalLevel(const Value minFatal);
    static Value fatalLevel();

private:
    Value mValue=$nullLevel;
    Flag mFlag=$nullLevelFlag;
    static Value smFatalLevel;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(LogLevel::Flags)

inline LogLevel::Value LogLevel::value() const { return mValue; }
inline bool LogLevel::isNull() const { return value() > $nullLevel; }
inline CText LogLevel::name() const { return name(value()); }
inline void LogLevel::fatalLevel(const Value minFatal) { smFatalLevel = minFatal; }
inline LogLevel::Value LogLevel::fatalLevel() { return smFatalLevel; }
inline LogLevel::MsgType LogLevel::msgType() const { return msgType(mValue); }
inline LogLevel::Flag LogLevel::flag() const { return mFlag; }
inline bool LogLevel::isWarn() const { return value() > LogLevel::TWarning; }
inline bool LogLevel::isError() const { return value() > LogLevel::$minError; }
inline bool LogLevel::isFatal() const { return value() > LogLevel::fatalLevel(); }
