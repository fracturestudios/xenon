
#include "xe/tracelogger.h"

/** Converts a time_t to a human-readable string */
const char *XeTraceLogger::timestr(time_t t)
{
    return ctime(&t);
}

/** Converts a XeTraceType to a human-readable string */
const char *XeTraceLogger::typestr(XeTraceType t)
{
    return xe_trace_type_str(t);
}

