
#include "xe/buttoninput.h"

XeButtonInput::XeButtonInput() : m_wasDown(false) { }

bool XeButtonInput::isUp() const { return !isDown(); }

bool XeButtonInput::isPressed() const { return isDown() && !m_wasDown; }

bool XeButtonInput::isReleased() const { return !isDown() && m_wasDown; }

void XeButtonInput::update(float)
{
    m_wasDown = isDown();
}

