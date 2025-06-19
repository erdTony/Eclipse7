#pragma once
/*!file LogMacros.h Internal MACROs for Logging */

#include "LogObject.h"
#include "LogItem.h"

#define LOGCTX(lvl) LogContext(lvl, Q_FUNC_INFO, __FILE__, __LINE__)
#define LOGMSG(lvl, msg) LogItem(LOGCTX(lvl), msg);
