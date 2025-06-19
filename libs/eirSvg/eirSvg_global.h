#pragma once
#include <QtCore/qglobal.h>

#if defined(EIRSVG_LIBRARY)
#define EIRSVG_EXPORT Q_DECL_EXPORT
#else
#define EIRSVG_EXPORT Q_DECL_IMPORT
#endif

