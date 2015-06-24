
#pragma once

#include "xe/global.h"
#include "xe/tracetype.h"

#include <ctime> // time_t

/** Abstract base for an object that receives log messages from xe_trace.
  * See XeFileLogger for an example
  */
class XE_EXPORT XeTraceLogger
{
public:
    /** Logs a line of output
      * @param timestamp The message's timestamp
      * @param type      The type of message to log
      * @param str       The string to log
      */
    virtual void log(time_t timestamp, XeTraceType type, const char *str) = 0;

protected:
    /** Converts a time_t to a human-readable string */
    const char *timestr(time_t);

    /** Converts a XeTraceType to a human-readable string */
    const char *typestr(XeTraceType);
};

