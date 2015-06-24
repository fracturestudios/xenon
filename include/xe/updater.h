
#pragma once

#include "xe/global.h"
#include "xe/updatable.h"

#include <QList>

/** Updatable that calls update() on one or more child objects each tick */
class XE_EXPORT XeUpdater : public XeUpdatable
{
public:
    /** Adds a child updatable */
    void attach(XeUpdatable *);
    /** Removes a child updatable */
    void detach(XeUpdatable *);

    /** Updates all attached children */
    void update(float dt);

private:
    QList<XeUpdatable*> m_targets;
};

