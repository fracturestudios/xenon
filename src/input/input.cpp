
#include "xe/input.h"
#include "xe/trace.h"

XeInput xe_input;

void XeButtonMap::map(const char *name, XeButtonInput *button)
{
    m_map[name] = button;
}

void XeButtonMap::unmap(const char *name)
{
    m_map.remove(name);
}

XeButtonInput *XeButtonMap::get(const char *name) const
{
    if (!m_map.contains(name))
    {
        xe_trace.warn("Unknown button input [%s] in XeButtonMap::get", name);
        return 0;
    }

    return m_map[name];
}

XeButtonInput *XeButtonMap::operator[](const char *name) const
{
    return get(name);
}

void XeAxisMap::map(const char *name, XeAxisInput *button)
{
    m_map[name] = button;
}

void XeAxisMap::unmap(const char *name)
{
    m_map.remove(name);
}

XeAxisInput *XeAxisMap::get(const char *name) const
{
    if (!m_map.contains(name))
    {
        xe_trace.warn("Unknown axis input [%s] in XeAxisMap::get", name);
        return 0;
    }

    return m_map[name];
}

XeAxisInput *XeAxisMap::operator[](const char *name) const
{
    return get(name);
}

bool XeInput::isDown(const char *name) const
{
    XeButtonInput *button = b[name];
    if (!button)
    {
        xe_trace.warn("XeInput::isDown(): button [%s] isn't mapped", name);
        return false;
    }

    return button->isDown();
}

bool XeInput::isUp(const char *name) const
{
    XeButtonInput *button = b[name];
    if (!button)
    {
        xe_trace.warn("XeInput::isUp(): button [%s] isn't mapped", name);
        return false;
    }

    return button->isUp();
}

bool XeInput::isPressed(const char *name) const
{
    XeButtonInput *button = b[name];
    if (!button)
    {
        xe_trace.warn("XeInput::isPressed(): button [%s] isn't mapped", name);
        return false;
    }

    return button->isPressed();
}

bool XeInput::isReleased(const char *name) const
{
    XeButtonInput *button = b[name];
    if (!button)
    {
        xe_trace.warn("XeInput::isReleased(): button [%s] isn't mapped", name);
        return false;
    }

    return button->isReleased();
}

float XeInput::value(const char *name) const
{
    XeAxisInput *axis = a[name];
    if (!axis)
    {
        xe_trace.warn("XeInput::value(): axis [%s] isn't mapped", name);
        return 0.f;
    }

    return axis->value();
}

float XeInput::value(const char *name, float min, float max) const
{
    XeAxisInput *axis = a[name];
    if (!axis)
    {
        xe_trace.warn("XeInput::value(): axis [%s] isn't mapped", name);
        return 0.f;
    }

    return axis->value(min, max);
}

