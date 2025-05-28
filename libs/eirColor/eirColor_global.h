#ifndef EIRCOLOR_GLOBAL_H
#define EIRCOLOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRCOLOR_LIBRARY)
#define EIRCOLOR_EXPORT Q_DECL_EXPORT
#else
#define EIRCOLOR_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRCOLOR_GLOBAL_H
