
#pragma once

#include "xe/global.h"
#include "xe/updatable.h"

/** Abstract base for a button input */
class XE_EXPORT XeButtonInput : public XeUpdatable
{
public:
    XeButtonInput();

    /** Gets the ID of this button, unique to the device it belongs to */
    virtual const char *id() const = 0;
    /** Gets the human-readable name of this button */
    virtual const char *name() const = 0;

    /** Gets the ID of this button's parent device. The device can be 
      * retrieved using xe_kernel.input().device(XeButtonInput::deviceID())
      */
    virtual const char *deviceID() const = 0;

    /** Gets a value indicating whether the user is currently pressing the button */
    virtual bool isDown() const = 0;
    /** Gets a value indicating whether the user is currently not pressing the button */
    virtual bool isUp() const;

    /** Gets a value indicating whether this is the first update tick for which the user
      * is pressing this button. That is, the user is currently pressing the button and
      * was not pressing the button during the previous tick. Useful for fire-once events
      * like navigating through a menu
      */
    virtual bool isPressed() const;
    /** Gets a value indicating whether this is the first update tick for which the user
     * is not pressing this button. That is, the user is currently not pressing the button
     * and was pressing the button during the previous tick. Useful for fire-once events
     */
    virtual bool isReleased() const;

    /** Updates this button. This call must be made *after* all possible input processing
      * for this tick is complete, or the values returned by isPressed()/isReleased() may
      * be incorrect. The kernel handles this automatically
      */
    virtual void update(float dt);

protected:
    /** Whether isDown() was true during the previous update tick */
    bool m_wasDown;
};

