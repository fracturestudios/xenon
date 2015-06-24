
#pragma once

#include "xe/global.h"
#include "xe/updatable.h"

/** Abstract base for an axis input */
class XE_EXPORT XeAxisInput : XeUpdatable
{
public:
    /** Gets the ID of this axis, unique to the device it belongs to */
    virtual const char *id() const = 0;
    /** Gets the human-readable name of this axis */
    virtual const char *name() const = 0;

    /** Gets the ID of this axis's parent device. The device can be 
      * retrieved using xe_kernel.input().device(XeAxisInput::deviceID())
      */
    virtual const char *deviceID() const = 0;

    /** Gets the current value of this axis, between 0 and 1 inclusive */
    virtual float value() const = 0;
    /** Gets the current value of this axis, linearly scaled between min
      * and max inclusive
      */
    virtual float value(float min, float max) const;

    /** Does per-frame updating needed by this axis */
    virtual void update(float dt);
};

