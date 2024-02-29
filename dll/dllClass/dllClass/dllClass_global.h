#ifndef DLLCLASS_GLOBAL_H
#define DLLCLASS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLCLASS_LIBRARY)
#  define DLLCLASS_EXPORT Q_DECL_EXPORT
#else
#  define DLLCLASS_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLCLASS_GLOBAL_H
