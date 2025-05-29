#ifndef EIRREMOTE_GLOBAL_H
#define EIRREMOTE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRREMOTE_LIBRARY)
#define EIRREMOTE_EXPORT Q_DECL_EXPORT
#else
#define EIRREMOTE_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRREMOTE_GLOBAL_H
