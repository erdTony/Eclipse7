#ifndef EIRFACEREC_GLOBAL_H
#define EIRFACEREC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRFACEREC_LIBRARY)
#define EIRFACEREC_EXPORT Q_DECL_EXPORT
#else
#define EIRFACEREC_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRFACEREC_GLOBAL_H
