
#include "mouse.h"

#include "xe/trace.h"

static const char *button_ids[(int)qtmouse::NUM_BUTTONS] = 
{
    "left",
    "middle",
    "right",
    "x1",
    "x2",
    "scrollup",
    "scrolldown"
};

static const char *button_names[(int)qtmouse::NUM_BUTTONS] = 
{
    "Left Click",
    "Middle Click",
    "Right Click",
    "X1",
    "X2",
    "Scroll Up",
    "Scroll Down",
};

static const char *axis_ids[(int)qtmouse::NUM_AXES] =
{
    "Horizontal",
    "Vertical",
};

static const char *axis_names[(int)qtmouse::NUM_AXES] = 
{
    "Move (Horizontal)",
    "Mose (Vertical)",
};

static const char *device_id = "Mouse";
static const char *device_name = "Mouse";

static bool button_from_id(const char *id, qtmouse::ButtonID *out = 0)
{
    for (int i = 0; i < (int)qtmouse::NUM_BUTTONS; ++i)
    {
        if (strcmp(id, button_ids[i]) == 0)
        {
            if (out) *out = (qtmouse::ButtonID)i;
            return true;
        }
    }

    return false;
}

static bool axis_from_id(const char *id, qtmouse::AxisID *out = 0)
{
    for (int i = 0; i < (int)qtmouse::NUM_AXES; ++i)
    {
        if (strcmp(id, axis_ids[i]) == 0)
        {
            if (out) *out = (qtmouse::AxisID)i;
            return true;
        }
    }

    return false;
}

static bool button_from_qt(Qt::MouseButtons b, qtmouse::ButtonID *out = 0)
{
    switch (b)
    {
    case Qt::LeftButton:
        if (out) *out = qtmouse::LeftButton;
        return true;
    case Qt::MidButton:
        if (out) *out = qtmouse::MiddleButton;
        return true;
    case Qt::RightButton:
        if (out) *out = qtmouse::RightButton;
        return true;
    case Qt::XButton1:
        if (out) *out = qtmouse::X1Button;
        return true;
    case Qt::XButton2:
        if (out) *out = qtmouse::X2Button;
        return true;
    default:
        return false;
    }
}

const char *QtMouseButton::id() const 
{
    return button_ids[buttonID];
}

const char *QtMouseButton::name() const
{
    return button_names[buttonID];
}

const char *QtMouseButton::deviceID() const
{
    return device_id;
}

bool QtMouseButton::isDown() const
{
    return down;
}

const char *QtMouseAxis::id() const
{
    return axis_ids[axisID];
}

const char *QtMouseAxis::name() const
{
    return axis_names[axisID];
}

const char *QtMouseAxis::deviceID() const 
{
    return device_id;
}

float QtMouseAxis::value() const
{
    return axisValue;
}

QtMouse::QtMouse()
{
    for (int i = 0; i < (int)qtmouse::NUM_BUTTONS; ++i)
    {
        m_buttons[i].buttonID = (qtmouse::ButtonID)i;
        m_buttons[i].down = false;
    }

    for (int i = 0; i < (int)qtmouse::NUM_AXES; ++i)
    {
        m_axes[i].axisID = (qtmouse::AxisID)i;
        m_axes[i].axisValue = 0.f;
    }
}

QtWindow *QtMouse::window() const
{
    return m_window;
}

void QtMouse::setWindow(QtWindow *w)
{
    m_window = w;
}

const char *QtMouse::id() const
{
    return device_id;
}

const char *QtMouse::name() const
{
    return device_name;
}

bool QtMouse::hasAxis(const char *id) const
{
    return axis_from_id(id);
}

bool QtMouse::hasButton(const char *id) const
{
    return button_from_id(id);
}

void QtMouse::axes(QList<const char *> &out)
{
    for (int i = 0; i < (int)qtmouse::NUM_BUTTONS; ++i)
        out.append(button_ids[i]);
}

void QtMouse::buttons(QList<const char *> &out)
{
    for (int i = 0; i < (int)qtmouse::NUM_AXES; ++i)
        out.append(axis_ids[i]);
}

XeAxisInput *QtMouse::axis(const char *id) const
{
    qtmouse::AxisID index;
    if (!axis_from_id(id, &index))
        return 0;

    return (XeAxisInput*)&m_axes[(int)index];
}

XeButtonInput *QtMouse::button(const char *id) const
{
    qtmouse::ButtonID index;
    if (!button_from_id(id, &index))
        return 0;

    return (XeButtonInput*)&m_buttons[(int)index];
}

void QtMouse::update(float dt)
{
    for (unsigned i = 0; i < sizeof(m_buttons) / sizeof(m_buttons[0]); ++i)
        m_buttons[i].update(dt);

    for (unsigned i = 0; i < sizeof(m_axes) / sizeof(m_axes[0]); ++i)
        m_axes[i].axisValue = 0.f;

    m_buttons[(int)qtmouse::ScrollUpButton].down = false;
    m_buttons[(int)qtmouse::ScrollDownButton].down = false;
}

void QtMouse::mousedown(QMouseEvent *ev)
{
    qtmouse::ButtonID i;
    if (button_from_qt(ev->button(), &i))
        m_buttons[(int)i].down = true;
}

void QtMouse::mouseup(QMouseEvent *ev)
{
    qtmouse::ButtonID i;
    if (button_from_qt(ev->button(), &i))
        m_buttons[(int)i].down = false;
}

void QtMouse::mousemove(int dx, int dy)
{
    float mult = .001f;

    m_axes[(int)qtmouse::HorizontalAxis].axisValue = dx * mult;
    m_axes[(int)qtmouse::VerticalAxis].axisValue = dy * mult;
}

void QtMouse::mousescroll(QWheelEvent *ev)
{
    xe_assert(ev->delta() != 0);

    int i = (int)(ev->delta() < 0 ? qtmouse::ScrollDownButton : qtmouse::ScrollUpButton);
    m_buttons[i].down = true;
}

