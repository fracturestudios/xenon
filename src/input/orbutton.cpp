
#include "xe/orbutton.h"

void XeOrButton::attach(XeButtonInput *b)
{
    m_children.append(b);
    rename();
}

void XeOrButton::detach(XeButtonInput *b)
{
    m_children.removeOne(b);
    rename();
}

bool XeOrButton::isAttached(XeButtonInput *b) const
{
    return m_children.contains(b);
}

bool XeOrButton::isDown() const
{
    foreach (XeButtonInput *b, m_children)
        if (b->isDown())
            return true;

    return false;
}

const char *XeOrButton::id() const
{
    return m_id.toUtf8().data();
}

const char *XeOrButton::name() const
{
    return m_name.toUtf8().data();
}

const char *XeOrButton::deviceID() const
{
    return "anonymous";
}

void XeOrButton::rename()
{
    m_id = "or";
    m_name = "";

    for (int i = 0; i < m_children.count(); ++i)
    {
        XeButtonInput *b = m_children[i];
        
        m_id += QString("-") + b->id();

        if (i > 0) 
            m_name += " or ";
        m_name += QString("(") + b->name() + ")";
    }
}

