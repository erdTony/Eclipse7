#ifndef EIRGUI_GLOBAL_H
#define EIRGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRGUI_LIBRARY)
#define EIRGUI_EXPORT Q_DECL_EXPORT
#else
#define EIRGUI_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRGUI_GLOBAL_H
