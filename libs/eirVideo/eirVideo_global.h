#ifndef EIRVIDEO_GLOBAL_H
#define EIRVIDEO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EIRVIDEO_LIBRARY)
#define EIRVIDEO_EXPORT Q_DECL_EXPORT
#else
#define EIRVIDEO_EXPORT Q_DECL_IMPORT
#endif

#endif // EIRVIDEO_GLOBAL_H
