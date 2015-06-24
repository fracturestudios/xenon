
#include "xe/filelogger.h"

XeFileLogger::XeFileLogger(FILE *f) : m_writer(f) { }

XeFileLogger::XeFileLogger(const char *path) : m_file(path), m_writer(&m_file)
{
    m_file.open(QFile::WriteOnly | QFile::Truncate);
}

void XeFileLogger::log(time_t timestamp, XeTraceType type, const char *msg)
{
    m_writer << "[" << timestr(timestamp) << "] " << typestr(type) << ": " << msg << "\n";
}

