
#include "xe/andbutton.h"

void XeAndButton::attach(XeButtonInput *b)
{
    m_children.append(b);
    rename();
}

void XeAndButton::detach(XeButtonInput *b)
{
    m_children.removeOne(b);
    rename();
}

bool XeAndButton::isAttached(XeButtonInput *b) const
{
    return m_children.contains(b);
}

bool XeAndButton::isDown() const
{
    foreach (XeButtonInput *b, m_children)
        if (!b->isDown())
            return false;

    return true;
}

const char *XeAndButton::id() const
{
    return m_id.toUtf8().data();
}

const char *XeAndButton::name() const
{
    return m_name.toUtf8().data();
}

const char *XeAndButton::deviceID() const
{
    return "anonymous";
}

void XeAndButton::rename()
{
    m_id = "and";
    m_name = "";

    for (int i = 0; i < m_children.count(); ++i)
    {
        XeButtonInput *b = m_children[i];
        
        m_id += QString("-") + b->id();

        if (i > 0) 
            m_name += " + ";
        m_name += QString("(") + b->name() + ")";
    }
}

