
#include "xe/updater.h"

void XeUpdater::attach(XeUpdatable *u)
{
    m_targets.append(u);
}

void XeUpdater::detach(XeUpdatable *u)
{
    m_targets.removeOne(u);
}

void XeUpdater::update(float dt)
{
    foreach (XeUpdatable *u, m_targets)
        u->update(dt);
}

