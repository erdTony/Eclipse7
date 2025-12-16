#ifndef EIRLOGGER_GLOBAL_H
#define EIRLOGGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRLOGGER_LIBRARY)
#define EIRLOGGER_EXPORT Q_DECL_EXPORT
#else
#define EIRLOGGER_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRLOGGER_GLOBAL_H
