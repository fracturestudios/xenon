
#pragma once

#include "xe/global.h"

/** Interface for an object that needs to be updated once per game tick.
  * Updatable objects can be added to the xe_kernel's pre- or post-
  * updater to be automatically updated once per tick before or after
  * (respectively) the current GameScreen is updated
  */
class XE_EXPORT XeUpdatable
{
public:
    /** Updates this object
      * @param dt The time elapsed since the last tick, in partial seconds
      */
    virtual void update(float dt) = 0;
};

