#pragma once
/*!file Log.h 'Public' interface to logging */

#define LOG() (Log::instance())

#include "LogEntry.h"
#include "LogMacros.h"
#include "LogObject.h"
#include "BaseLogOutput.h"

#define LOGOUTURL(url) LOG()->add(new LogOutput(url));

#define FNENTER() { LogEntry le(LogLevel::FnEnter, "Enter:"); }
#define FNSLOT() { LogEntry le(LogLevel::FnEnter, "Slot:"); }
#define FNARG(arg) { LogEntry le(LogLevel::FnArg, #arg, QVariant(arg)); }
#define CONNECT(sndr, sig, rcvr, slt) \
    { LogEntry(sndr, #sndr, sig, rcvr, #rcvr, slt); }
#define DISCON(sndr, sig, rcvr, slt) \
    { LogEntry(sndr, #sndr, sig, rcvr, #rcvr, slt, false); }
#define UNUSED(var) { LogEntry le(LogLevel::Unused, #var); Q_UNUSED(var); }

#define UINFOMSG(msg) { LogEntry le(LogLevel::UInfo, msg); }
#define TINFOMSG(msg) { LogEntry le(LogLevel::TInfo, msg); }
#define INFOMSG(msg) UINFOMSG(msg); UINFOMSG(msg);
