#ifndef DLL_PARSER_GLOBAL_H
#define DLL_PARSER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLL_PARSER_LIBRARY)
#  define DLL_PARSER_EXPORT Q_DECL_EXPORT
#else
#  define DLL_PARSER_EXPORT Q_DECL_IMPORT
#endif

#endif // DLL_PARSER_GLOBAL_H
