#ifndef EIRXML_GLOBAL_H
#define EIRXML_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRXML_LIBRARY)
#define EIRXML_EXPORT Q_DECL_EXPORT
#else
#define EIRXML_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRXML_GLOBAL_H
