
#include "xe/axisbutton.h"

XeAxisButton::XeAxisButton(XeAxisInput *child, const XeRangeF &active) : m_axis(child), m_range(active) { }

XeAxisInput *XeAxisButton::child() const
{
    return m_axis;
}

void XeAxisButton::setChild(XeAxisInput *child) 
{
    m_axis = child;
    m_name = child->name();
    m_id = child->id();
}

const XeRangeF &XeAxisButton::activationRange() const
{
    return m_range;
}

void XeAxisButton::setActivationRange(const XeRangeF &range)
{
    m_range = range;
}

const char *XeAxisButton::id() const
{
    return m_id.toUtf8().data();
}

const char *XeAxisButton::name() const
{
    return m_name.toUtf8().data();
}

const char *XeAxisButton::deviceID() const
{
    return "anonymous";
}

bool XeAxisButton::isDown() const
{
    return m_range.contains(m_axis->value());
}

