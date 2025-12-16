#pragma once

#include "LogLevel.h"

class LogFilter
{
public: // ctors
    LogFilter();
    LogFilter(const LogLevel::FlagMask fm);
    LogFilter(const LogLevel::Value max,
              const LogLevel::Value min);
    LogFilter(const LogLevel::FlagMask fm,
              const LogLevel::Value max,
              const LogLevel::Value min);


public: // const
    bool evaluate(const LogLevel::Value lvl) const;

public: // non-const
    void clear();
    void set(const LogLevel::FlagMask fm);
    void set(const LogLevel::Value max,
             const LogLevel::Value min);
    void set(const LogLevel::FlagMask fm,
             const LogLevel::Value max,
             const LogLevel::Value min);
    void setMask(const AText &tx);
    void setMax(const AText &tx);
    void setMin(const AText &tx);

private:
    LogLevel::FlagMask mMask;
    LogLevel::Value mMaxValue;
    LogLevel::Value mMinValue;
};
