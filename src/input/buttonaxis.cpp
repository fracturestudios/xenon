
#include "xe/buttonaxis.h"

void XeButtonAxis::attach(XeButtonInput *button, float upval, float downval)
{
    m_buttons.append(ButtonValue(button, upval, downval));

    m_id = "";
    m_name = "";

    for (int i = 0; i < m_buttons.count(); ++i)
    {
        if (i > 0) m_id += "-";
        m_id += m_buttons[i].button->id();

        if (i > 0) m_name += ", ";
        m_name += m_buttons[i].button->name();
    }
}

void XeButtonAxis::detach(XeButtonInput *button)
{
    for (int i = 0; i < m_buttons.count(); ++i)
    {
        if (m_buttons[i].button == button)
        {
            m_buttons.removeAt(i);
            break;
        }
    }
}

bool XeButtonAxis::isAttached(XeButtonInput *button) const
{
    for (int i = 0; i < m_buttons.count(); ++i)
        if (m_buttons[i].button == button)
            return true;

    return false;
}

const char *XeButtonAxis::id() const
{
    return m_id.toUtf8().data();
}

const char *XeButtonAxis::name() const
{
    return m_name.toUtf8().data();
}

const char *XeButtonAxis::deviceID() const
{
    return "anonymous";
}

float XeButtonAxis::value() const
{
    float val = 0;
    foreach (const ButtonValue &b, m_buttons)
        val += b.button->isDown() ? b.downval : b.upval;
    
    return val;
}

