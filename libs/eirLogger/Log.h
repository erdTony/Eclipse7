#pragma once
/*!file Log.h 'Public' interface to logging */

#define LOG() (Log::instance())

#include "LogEntry.h"
#include "LogMacros.h"
#include "LogObject.h"
#include "LogOutput.h"

#define LOGOUTURL(url) LOG()->add(new LogOutput(url));


#define UINFOMSG(msg) { LogEntry le(LogLevel::UInfo, msg); }
#define TINFOMSG(msg) { LogEntry le(LogLevel::TInfo, msg); }
#define INFOMSG(msg) UINFOMSG(msg); UINFOMSG(msg);
