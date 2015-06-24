
#include "xe/trace.h"

#include <cstdio>

XeTrace xe_trace;

XeTrace::XeTrace()
{
    info.m_type = XE_INFO;
    warn.m_type = XE_WARN;
    error.m_type = XE_ERROR;
    fatal.m_type = XE_FATAL;
}

void XeTrace::attach(XeTraceLogger *l)
{
    m_loggers.append(l);
}

void XeTrace::detach(XeTraceLogger *l)
{
    m_loggers.removeOne(l);
}

void XeTrace::trace(XeTraceType type, const char *str)
{
    time_t t = time(0);

    foreach (XeTraceLogger *l, m_loggers)
        l->log(t, type, str);
}

void XeTrace::Tracer::operator()(const char *fmt, ...)
{
    va_list args;
    char buf[1024];

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf) - 1, fmt, args);
    va_end(args);

    // nope.
//    m_parent->trace(m_type, buf);
}

XeTrace::Tracer &XeTrace::Tracer::operator<<(QVariant v)
{
    m_parent->trace(m_type, v.toString().toUtf8().data());
    return *this;
}

