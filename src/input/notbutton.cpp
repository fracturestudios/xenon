
#include "xe/notbutton.h"

XeNotButton::XeNotButton() : m_child(0) { }

XeNotButton::XeNotButton(XeButtonInput *child) : m_child(child) 
{ 
    setChild(child); // generate m_id/m_name 
}

XeButtonInput *XeNotButton::child() const
{
    return m_child;
}

void XeNotButton::setChild(XeButtonInput *child)
{
    m_child = child;
    if (child)
    {
        m_id = QString("not-") + child->id();
        m_name = QString("Not (") + child->name() + ")";
    }
    else
    {
        m_id = "not-<nil>";
        m_name = "<nil>";
    }
}

const char *XeNotButton::id() const
{
    return m_id.toUtf8().data();
}

const char *XeNotButton::name() const
{
    return m_name.toUtf8().data();
}

const char *XeNotButton::deviceID() const
{
    return "anonymous";
}

bool XeNotButton::isDown() const
{
    return m_child && !m_child->isDown();
}

