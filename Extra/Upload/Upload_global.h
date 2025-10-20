#ifndef UPLOAD_GLOBAL_H
#define UPLOAD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UPLOAD_LIBRARY)
#  define UPLOAD_EXPORT Q_DECL_EXPORT
#else
#  define UPLOAD_EXPORT Q_DECL_IMPORT
#endif

#endif // UPLOAD_GLOBAL_H
