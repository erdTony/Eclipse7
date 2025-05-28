#ifndef EIRQTCV_GLOBAL_H
#define EIRQTCV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRQTCV_LIBRARY)
#define EIRQTCV_EXPORT Q_DECL_EXPORT
#else
#define EIRQTCV_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRQTCV_GLOBAL_H
