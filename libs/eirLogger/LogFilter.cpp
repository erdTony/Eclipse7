#include "LogFilter.h"

LogFilter::LogFilter() { clear(); }
LogFilter::LogFilter(const LogLevel::FlagMask fm) { set(fm); }
LogFilter::LogFilter(const LogLevel::Value max, const LogLevel::Value min) { set(max, min); }
LogFilter::LogFilter(const LogLevel::FlagMask fm, const LogLevel::Value max, const LogLevel::Value min) { set(fm, max, min); }

bool LogFilter::evaluate(const LogLevel::Value lvl) const
{
    if (mMask && (! (mMask & (1 << lvl))))  return false;
    if (mMaxValue < lvl)                    return false;
    if (mMinValue > lvl)                    return false;
    return true;
}

void LogFilter::clear()
{
    mMask = LogLevel::FlagMask(0),
        mMaxValue = LogLevel::Maximum,
        mMinValue = LogLevel::Minimum;

}

void LogFilter::set(const LogLevel::FlagMask fm)
{
    mMask = fm,
        mMaxValue = LogLevel::Maximum,
        mMinValue = LogLevel::Minimum;
}

void LogFilter::set(const LogLevel::Value max,
                    const LogLevel::Value min)
{
    mMask = LogLevel::FlagMask(0x7FFFFFFF),
        mMaxValue = max,
        mMinValue = min;
}

void LogFilter::set(const LogLevel::FlagMask fm,
                    LogLevel::Value max,
                    const LogLevel::Value min)
{
    mMask = fm,
        mMaxValue = max,
        mMinValue = min;

}

void LogFilter::setMask(const AText &tx)
{

}

void LogFilter::setMax(const AText &tx)
{

}

void LogFilter::setMin(const AText &tx)
{

}

