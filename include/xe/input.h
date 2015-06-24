
#pragma once

#include "xe/axisinput.h"
#include "xe/buttoninput.h"
#include "xe/global.h"

#include <QHash>

/** Maps virtual button names to button objects */
class XE_EXPORT XeButtonMap
{
public:
    void map(const char *name, XeButtonInput *button);
    void unmap(const char *name);

    XeButtonInput *get(const char *name) const;
    XeButtonInput *operator[](const char *name) const;

private:
    QHash<QString, XeButtonInput*> m_map;
};

/** Maps virtual axis names to axis objects */
class XE_EXPORT XeAxisMap
{
public:
    void map(const char *name, XeAxisInput *button);
    void unmap(const char *name);

    XeAxisInput *get(const char *name) const;
    XeAxisInput *operator[](const char *name) const;

private:
    QHash<QString, XeAxisInput*> m_map;
};

/** Manages the application-level button and axis maps */
class XE_EXPORT XeInput
{
public:
    /** Maps virtual names to axis inputs */
    XeAxisMap a;

    /** Maps virtual names to butotn inputs */
    XeButtonMap b;

    bool isDown(const char *name) const;
    bool isUp(const char *name) const;
    bool isPressed(const char *name) const;
    bool isReleased(const char *name) const;

    float value(const char *name) const;
    float value(const char *name, float min, float max) const;
};

extern XE_EXPORT XeInput xe_input;

