#ifndef LIBS_GLOBAL_H
#define LIBS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBS_LIBRARY)
#  define LIBS_EXPORT Q_DECL_EXPORT
#else
#  define LIBS_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBS_GLOBAL_H
