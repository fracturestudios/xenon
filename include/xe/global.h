
#pragma once

#include <QtCore/qglobal.h>

#include "xe/config.h"

#if XE_NOLIB
#   define XE_EXPORT
#else
#   if defined(XENON_LIBRARY)
#       define XE_EXPORT Q_DECL_EXPORT
#   else
#       define XE_EXPORT Q_DECL_IMPORT
#   endif
#endif

