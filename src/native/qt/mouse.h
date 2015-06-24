
#pragma once

#include "xe/axisinput.h"
#include "xe/buttoninput.h"
#include "xe/inputdevice.h"

#include "window.h"

#include <QMouseEvent>
#include <QString>
#include <QWheelEvent>

namespace qtmouse
{
    enum ButtonID
    {
        LeftButton,
        MiddleButton,
        RightButton,
        X1Button,
        X2Button,
        ScrollUpButton,
        ScrollDownButton,

        NUM_BUTTONS
    };

    enum AxisID
    {
        HorizontalAxis,
        VerticalAxis,

        NUM_AXES
    };
};

class QtMouseButton : public XeButtonInput
{
public:
    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    bool isDown() const;

    bool down;
    qtmouse::ButtonID buttonID;
};

class QtMouseAxis : public XeAxisInput
{
public:
    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    float value() const;

    float axisValue;
    qtmouse::AxisID axisID;
};

class QtMouse : public XeInputDevice
{
public:
    QtMouse();

    QtWindow *window() const;
    void setWindow(QtWindow*);

    const char *id() const;
    const char *name() const;

    bool hasAxis(const char *id) const;
    bool hasButton(const char *id) const;

    void axes(QList<const char *> &out);
    void buttons(QList<const char *> &out);

    XeAxisInput *axis(const char *id) const;
    XeButtonInput *button(const char *id) const;

    void update(float);

private:
    QtMouseButton m_buttons[(int)qtmouse::NUM_BUTTONS];
    QtMouseAxis m_axes[(int)qtmouse::NUM_AXES];
    QtWindow *m_window;

    friend class QtWindow;

    void mousedown(QMouseEvent *);
    void mouseup(QMouseEvent *);
    void mousemove(int dx, int dy);
    void mousescroll(QWheelEvent *);
};

