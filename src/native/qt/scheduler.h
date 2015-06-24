
#pragma once

#include "../scheduler.h"

class QtScheduler : public XeScheduler
{
public:
    void setUpdateCallback(XeSchedulerCallback f, void *arg);
    void setRenderCallback(XeSchedulerCallback f, void *arg);

    void tick();

private:
    XeSchedulerCallback update; void *updateArg;
    XeSchedulerCallback render; void *renderArg;

    friend class QtWindow;

    void onupdate(float dt);
    void onrender(float dt);
};

