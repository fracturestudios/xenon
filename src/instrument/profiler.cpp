
#include "xe/profiler.h"
#include "xe/trace.h"

#include <QHashIterator>
#include <QStringList>

XeProfilerSection::XeProfilerSection(const char *name) : m_name(name) { }

const char *XeProfilerSection::name() const 
{
    return m_name;
}

void XeProfilerSection::setName(const char *name) 
{
    m_name = name;
}

float XeProfilerSection::dt() const
{
    return m_dt;
}

void XeProfilerSection::begin()
{
    m_time.start();
}

void XeProfilerSection::end()
{
    m_dt = .001f * m_time.elapsed();
}

XeProfilerSection *XeProfiler::get(const char *name)
{
    if (!m_sections.contains(name))
        m_sections[name] = new XeProfilerSection(name);
    
    return m_sections[name];
}

const XeProfilerSection *XeProfiler::section(const char *name)
{
    return get(name);
}

const XeProfilerSection *XeProfiler::operator[](const char *name)
{
    return get(name); 
}

void XeProfiler::sections(QList<XeProfilerSection*> &out) const
{
    QHashIterator<QString, XeProfilerSection*> it(m_sections);
    while (it.hasNext())
        out.append(it.next().value());
}

void XeProfiler::begin(const char *name)
{
    get(name)->begin();
}

void XeProfiler::end(const char *name)
{
    get(name)->end();
}

void XeProfiler::update(float dt)
{
    m_dt = dt;

    XeProfilerSection *other = m_sections.contains("Other") ? m_sections.take("Other") : 0;
    if (!other)
        other = new XeProfilerSection("Other");

    float total = 0.f;
    QHashIterator<QString, XeProfilerSection*> it(m_sections);
    while (it.hasNext())
        total += it.next().value()->dt();

    other->m_dt = dt - total;
    m_sections["Other"] = other;
}

void XeProfiler::log() const
{
    const char *titles = "\tTime\t\t%\t\tSection";
    const char *fmt = "\t%.3f\t\t%.3f\t\t%s";

    xe_trace.info << "XeProfiler"
                  << titles;

    QStringList keys = m_sections.keys();
    keys.sort();

    foreach (const QString& section, keys)
    {
        float t = m_sections[section]->dt();
        float amt = t / m_dt;

        xe_trace.info(fmt, t, amt, section.toUtf8().data());
    }
}

void XeProfiler::render(float) const
{
    xe_trace.error << "XeProfiler::render() not yet implemented";
}

