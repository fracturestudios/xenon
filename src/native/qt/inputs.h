
#pragma once

#include "../inputs.h"

#include "keyboard.h"
#include "mouse.h"

class QtInputs : public XeInputs
{
public:
    QtInputs();

    QtKeyboard *keyboard() const;
    void setKeyboard(QtKeyboard *);

    QtMouse *mouse() const;
    void setMouse(QtMouse *);

    bool hasDevice(const char *id);

    void devices(QList<const char *> &out);

    XeInputDevice *device(const char *id);

    void update(float dt);

private:
    QtKeyboard *m_keyboard;
    QtMouse *m_mouse;
};

