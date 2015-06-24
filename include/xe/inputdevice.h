
#pragma once

#include "xe/axisinput.h"
#include "xe/buttoninput.h"
#include "xe/global.h"
#include "xe/updatable.h"

#include <QList>

/** Abstract base for an input device with one or more
  * attached inputs
  */
class XE_EXPORT XeInputDevice : public XeUpdatable
{
public:
    /** Gets the unique ID of this input device */
    virtual const char *id() const = 0;
    /** Gets the human-readable name of this input device */
    virtual const char *name() const = 0;

    /** Gets a value indicating whether or not this device has an axis or
      * a button with the given unique ID
      */
    virtual bool hasInput(const char *id) const;
    /** Gets a value indicating whether or not this device has a button 
      * with the given unique ID
      */
    virtual bool hasAxis(const char *id) const = 0;
    /** Gets a value indicating whether or not this device has a axis 
      * with the given unique ID
      */
    virtual bool hasButton(const char *id) const = 0;

    /** Appends all axis inputs available from this device to the given list */
    virtual void axes(QList<const char *> &out) = 0;

    /** Appends all button inputs available from this device to the given list */
    virtual void buttons(QList<const char *> &out) = 0;

    /** Gets the axis attached to this device with the given unique ID.
      * If no such axis exists, returns NULL.
      */
    virtual XeAxisInput *axis(const char *id) const = 0;
    /** Gets the button attached to this device with the given unique ID.
      * If no such button exists, returns NULL.
      */
    virtual XeButtonInput *button(const char *id) const = 0;
};

