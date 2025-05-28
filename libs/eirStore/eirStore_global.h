#ifndef EIRSTORE_GLOBAL_H
#define EIRSTORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRSTORE_LIBRARY)
#define EIRSTORE_EXPORT Q_DECL_EXPORT
#else
#define EIRSTORE_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRSTORE_GLOBAL_H
