
#pragma once

#include <QFile>
#include <QTextStream>

#include "xe/global.h"
#include "xe/tracelogger.h"

class XE_EXPORT XeFileLogger : public XeTraceLogger
{
public:
    XeFileLogger(FILE*);
    XeFileLogger(const char *path);

    void log(time_t, XeTraceType, const char*);

private:
    QFile m_file;
    QTextStream m_writer;
};

