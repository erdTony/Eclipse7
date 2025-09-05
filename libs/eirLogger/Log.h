#pragma once
/*!file Log.h 'Public' interface to logging */

#define LOG() (Log::instance())

#include "LogEntry.h"
#include "LogMacros.h"
#include "LogObject.h"
#include "LogOutput.h"

//#define LOGOUTSTD() LOG()->add(new LogOutText(true));
//#define LOGOUTDEF() LOG()->add(new LogOutText(false));
#define LOGOUTURL(url) LOG()->add(new LogOutput(url));


#define UINFOMSG(msg) { LogEntry le(LogLevel::UInfo, msg); qInfo() <<  le.xport(); }
#define TINFOMSG(msg) LogEntry le(LogLevel::TInfo, msg); qInfo() <<  le;

//#define LOGENTRYMSG(lvl, msg)
//#define UINFOMSG(msg) qInfo() <<  LOGENTRYMSG(LogLevel::UInfo, msg)
//#define TINFOMSG(msg) qInfo() <<  LOGENTRYMSG(LogLevel::TInfo, msg)
#define INFOMSG(msg) UINFOMSG(msg); UINFOMSG(msg);
