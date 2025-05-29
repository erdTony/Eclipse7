#ifndef EIRLOGMGR_GLOBAL_H
#define EIRLOGMGR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRLOGMGR_LIBRARY)
#define EIRLOGMGR_EXPORT Q_DECL_EXPORT
#else
#define EIRLOGMGR_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRLOGMGR_GLOBAL_H
