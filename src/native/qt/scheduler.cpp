
#include "scheduler.h"

#include "xe/trace.h"

#include <QApplication>

void QtScheduler::setUpdateCallback(XeSchedulerCallback f, void *arg)
{
    update = f;
    updateArg = arg;
}

void QtScheduler::setRenderCallback(XeSchedulerCallback f, void *arg)
{
    render = f;
    renderArg = arg;
}

void QtScheduler::onupdate(float dt)
{
    if (!update)
        xe_die("No update callback -- kernel initialization fail");

    update(dt, updateArg);
}

void QtScheduler::onrender(float dt)
{
    if (!render)
        xe_die("No render callback -- kernel initialization fail");

    render(dt, renderArg);
}

void QtScheduler::tick()
{
    QApplication::processEvents();
}

