#ifndef EIRMATGEO_GLOBAL_H
#define EIRMATGEO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRMATGEO_LIBRARY)
#define EIRMATGEO_EXPORT Q_DECL_EXPORT
#else
#define EIRMATGEO_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRMATGEO_GLOBAL_H
