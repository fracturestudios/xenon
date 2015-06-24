
#pragma once

#include "xe/inputdevice.h"
#include "xe/updatable.h"

#include <QList>

/** Abstract base for an object that can enumerate input devices for
  * a given host interface. These objects are consumed by XeKernel
  * and are selected by which host interface the user chose at startup
  */
class XeInputs : public XeUpdatable
{
public:
    /** Gets a value indicating whether there is a device with the given ID */
    virtual bool hasDevice(const char *id) = 0;

    /** Fills out with the IDs of all available devices */
    virtual void devices(QList<const char *> &out) = 0;

    /** Gets the device with the supplied ID, or returns NULL if no such device exists */
    virtual XeInputDevice *device(const char *id) = 0; 

    /** Calls update on the input devices */
    virtual void update(float dt) = 0;
};

