
#include "xe/inputdevice.h"

bool XeInputDevice::hasInput(const char *id) const
{
    return hasAxis(id) || hasButton(id);
}

