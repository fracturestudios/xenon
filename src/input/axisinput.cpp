
#include "xe/axisinput.h"

float XeAxisInput::value(float min, float max) const
{
    return min + (max - min) * value();
}

void XeAxisInput::update(float) { }

