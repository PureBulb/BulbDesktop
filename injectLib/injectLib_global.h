#ifndef INJECTLIB_GLOBAL_H
#define INJECTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INJECTLIB_LIBRARY)
#  define INJECTLIB_EXPORT Q_DECL_EXPORT
#else
#  define INJECTLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // INJECTLIB_GLOBAL_H
