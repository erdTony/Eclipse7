#ifndef EIRQTVLAN_GLOBAL_H
#define EIRQTVLAN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRQTVLAN_LIBRARY)
#define EIRQTVLAN_EXPORT Q_DECL_EXPORT
#else
#define EIRQTVLAN_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRQTVLAN_GLOBAL_H
