#pragma once
/*!file Log.h 'Public' interface to logging */

#include "LogEntry.h"
#include "LogMacros.h"
#include "LogObject.h"
#include "LogOutput.h"
#include "LogOutText.h"

#define LOGHOOK() LOG()->hookQtMsg();
#define LOGUNHOOK() LOG()->unhookQtMsg();
#define LOGOUTSTD() LOG()->add(new LogOutText(true));
#define LOGOUTURL(url) LOG()->add(new LogOutText(url));


#define UINFOMSG(msg) { LogEntry le(LogLevel::UInfo, msg); qInfo() <<  le.xport(); }
#define TINFOMSG(msg) LogEntry le(LogLevel::TInfo, msg); qInfo() <<  le;

//#define LOGENTRYMSG(lvl, msg)
//#define UINFOMSG(msg) qInfo() <<  LOGENTRYMSG(LogLevel::UInfo, msg)
//#define TINFOMSG(msg) qInfo() <<  LOGENTRYMSG(LogLevel::TInfo, msg)
#define INFOMSG(msg) UINFOMSG(msg); UINFOMSG(msg);
