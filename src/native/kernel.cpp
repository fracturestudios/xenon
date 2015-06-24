
#include <GL/glew.h>

#include "xe/kernel.h"

#include "./init.h"
#include "./inputs.h"
#include "./scheduler.h"

#include "./qt/init.h"

XeKernel *xe_kernel = 0;

XeKernelInit XeKernelInitializers[] =
{
    &QtHostInit,
};

XeKernel::XeKernel(int& argc, char **argv) 
        : m_executing(false), m_nativeWindow(0), m_nativeInputs(0), m_nativeScheduler(0),
          m_preUpdate(new XeUpdater()), m_postUpdate(new XeUpdater()),
          m_argc(argc), m_argv(argv)
{ }

XeKernel::HostInterface XeKernel::hostInterface() const
{
    return m_host;
}

void XeKernel::setHostInterface(XeKernel::HostInterface host)
{
    m_host = host;
}

bool XeKernel::isExecuting() const
{
    return m_executing;
}

void XeKernel::exit()
{
    m_executing = false;
}

XeScreen *XeKernel::screen() const
{
    return m_screen.empty() ? 0 : m_screen.top();
}

void XeKernel::push(XeScreen *s)
{
    m_screen.push(s);
    if (s)
        s->load();
}

void XeKernel::pop()
{
    if (!m_screen.empty() && m_screen.top())
    {
        m_screen.top()->unload();
        m_screen.pop();
    }
}

void XeKernel::swap(XeScreen *s)
{
    pop();
    push(s);
}

XeWindow *XeKernel::window() const
{
    return (XeWindow*)m_nativeWindow;
}

bool XeKernel::hasDevice(const char *id) const
{
    XeInputs *i = (XeInputs*)m_nativeInputs;
    return i->hasDevice(id);
}

XeInputDevice *XeKernel::device(const char *id) const
{
    XeInputs *i = (XeInputs*)m_nativeInputs;
    return i->device(id);
}

XeUpdater *XeKernel::preUpdate() const
{
    return m_preUpdate;
}

XeUpdater *XeKernel::postUpdate() const
{
    return m_postUpdate;
}

int& XeKernel::argc() const
{
    return m_argc;
}

char **XeKernel::argv() const
{
    return m_argv;
}

static void update_callback(float dt, void *arg)
{
    XeKernel *kernel = (XeKernel*)arg;

    kernel->preUpdate()->update(dt);

    if (kernel->screen())
        kernel->screen()->update(dt);
    else
        kernel->exit();

    kernel->postUpdate()->update(dt);
}

static void render_callback(float dt, void *arg)
{
    XeKernel *kernel = (XeKernel*)arg;

    if (kernel->screen())
        kernel->screen()->render(dt);
    else
        kernel->exit();
}

void XeKernel::exec(XeScreen *first)
{
    XeKernelInitializers[(int)m_host](this,
                                      (XeWindow**)&m_nativeWindow, 
                                      (XeInputs**)&m_nativeInputs, 
                                      (XeScheduler**)&m_nativeScheduler);

    XeScheduler *sched = (XeScheduler*)m_nativeScheduler;
    sched->setUpdateCallback(&update_callback, this);
    sched->setRenderCallback(&render_callback, this);

    m_postUpdate->attach((XeInputs*)m_nativeInputs);

    glewInit();

    m_executing = true;
    xe_kernel = this;

    push(first);

    while (m_executing)
        sched->tick();
}

