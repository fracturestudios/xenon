
#include "inputs.h"

#include "xe/trace.h"

QtInputs::QtInputs() : m_keyboard(0), m_mouse(0) { }

QtKeyboard *QtInputs::keyboard() const
{
    return m_keyboard;
}

void QtInputs::setKeyboard(QtKeyboard *k)
{
    m_keyboard = k;
}

QtMouse *QtInputs::mouse() const
{
    return m_mouse;
}

void QtInputs::setMouse(QtMouse *m)
{
    m_mouse = m;
}

bool QtInputs::hasDevice(const char *id)
{
    return !strcmp(id, m_keyboard->id()) ||
           !strcmp(id, m_mouse->id()); 
}

void QtInputs::devices(QList<const char *> &out)
{
    out.append(m_keyboard->id());
    out.append(m_mouse->id());
}

XeInputDevice *QtInputs::device(const char *id)
{
    if (!strcmp(id, m_keyboard->id()))
    {
        return m_keyboard;
    }
    else if (!strcmp(id, m_mouse->id()))
    {
        return m_mouse;
    }
    else
    {
        xe_trace.warn("Unknown input device ID: %s", id);
        return 0;
    }
}

void QtInputs::update(float dt)
{
    m_keyboard->update(dt);
    m_mouse->update(dt);
}

