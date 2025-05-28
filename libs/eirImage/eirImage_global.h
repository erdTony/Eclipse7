#ifndef EIRIMAGE_GLOBAL_H
#define EIRIMAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRIMAGE_LIBRARY)
#define EIRIMAGE_EXPORT Q_DECL_EXPORT
#else
#define EIRIMAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRIMAGE_GLOBAL_H
