
#pragma once

#include "xe/global.h"

/** The types of log messages that can be sent to xe_trace. */
enum XeTraceType
{
    /** General informative / status message */
    XE_INFO,

    /** The game encountered a situation that may indicate a developer's mistake */
    XE_WARN,

    /** An error the game was able to recover from */
    XE_ERROR,

    /** An error causing an imminent crash */
    XE_FATAL,

    /** Echoed console commands */
    XE_CIN,

    /** Console command output */
    XE_COUT,
};

XE_EXPORT const char *xe_trace_type_str(XeTraceType type);

