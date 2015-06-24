
#pragma once

#include "xe/global.h"
#include "xe/updatable.h"

#include <QHash>
#include <QTime>

class XeProfilerSection;

/** A lightweight time-based profiler */
class XE_EXPORT XeProfiler : public XeUpdatable
{
public:
    /** Begins profiling a section of the update loop, e.g. "ai" or "physics" */
    void begin(const char *section);
    /** Ends profiling a section and takes a time sample */
    void end(const char *section);

    /** Gets a section by name */
    const XeProfilerSection* operator[](const char *section);
    const XeProfilerSection* section(const char *section);

    /** Gets all the sections */
    void sections(QList<XeProfilerSection*> &out) const;

    /** Performs per-frame updating required by the profiler */
    void update(float dt);

    /** Renders the profiler as a set of bars at the upper-left corner of the screen.
      * Useful for showing CPU usage spikes in real time
      */
    void render(float dt) const;

    /** Writes the contents of the profiler to xe_trace */
    void log() const;

private:
    QHash<QString, XeProfilerSection*> m_sections;
    float m_dt;

    XeProfilerSection *get(const char *section);
};

/** A sample taken for a section of the update loop */
class XE_EXPORT XeProfilerSection
{
public:
    XeProfilerSection(const char *name);

    const char *name() const;
    void setName(const char *);

    void begin();
    void end();

    float dt() const;

private:
    const char *m_name;
    float m_dt;
    QTime m_time;

    friend class XeProfiler;
};

