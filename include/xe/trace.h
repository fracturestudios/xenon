
#pragma once

#include <QList>
#include <QVariant>

#include "xe/global.h"
#include "xe/tracelogger.h"
#include "xe/tracetype.h"

/** Formats and logs trace messages */
class XE_EXPORT XeTrace 
{
public:
    /** Exposes printf- and cout-like interfaces for logging messages */
    class Tracer
    {
    public:
        void operator()(const char *fmt, ...);
        Tracer &operator<<(QVariant);

    private:
        XeTraceType m_type;
        XeTrace *m_parent;
        friend class XeTrace;
    };

    XeTrace();

    void attach(XeTraceLogger *);
    void detach(XeTraceLogger *);

    Tracer info;
    Tracer warn;
    Tracer error;
    Tracer fatal;

    void trace(XeTraceType type, const char *str);

private:
    QList<XeTraceLogger*> m_loggers;
};

/** The application's trace logger. Initialized by the active XeKernel when it
  * begins executing.
  */
extern XeTrace xe_trace;

#include <cstdlib> // abort

/** Sends an error to xe_trace.fatal and terminates the application forcibly */
#define xe_die(...) { xe_trace.fatal("__FILE__:__LINE__ : " __VA_ARGS__); abort(); }

/** Logs a message and aborts the application if the supplied condition is false */
#define xe_assert(condition, ...) { if (!(condition)) { xe_trace.fatal("__FILE__:__LINE__ : " __VA_ARGS__); abort(); } }

