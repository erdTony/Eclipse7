#pragma once
/*!file LogMacros.h Internal MACROs for Logging */

#include "LogEntry.h"
#include "LogObject.h"
#include "LogItem.h"

#define LOGENTRYARGS(lvl, fmt, args...) LogEntry(lvl, fmt, __VA_ARGS__)
#define LOGENTRYCOND(lvl, cond, args...) LogEntry(lvl, cond, __VA_ARGS__)


