#ifndef EIRSVG_GLOBAL_H
#define EIRSVG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRSVG_LIBRARY)
#define EIRSVG_EXPORT Q_DECL_EXPORT
#else
#define EIRSVG_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRSVG_GLOBAL_H
