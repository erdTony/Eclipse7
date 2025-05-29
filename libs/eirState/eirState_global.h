#ifndef EIRSTATE_GLOBAL_H
#define EIRSTATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRSTATE_LIBRARY)
#define EIRSTATE_EXPORT Q_DECL_EXPORT
#else
#define EIRSTATE_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRSTATE_GLOBAL_H
