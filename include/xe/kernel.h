
#pragma once

#include "xe/global.h"
#include "xe/inputdevice.h"
#include "xe/screen.h"
#include "xe/updater.h"
#include "xe/window.h"

#include <QStack>

class XE_EXPORT XeKernel
{
public:

    enum HostInterface
    {
        HOST_QT,
    };

    XeKernel(int& argc, char **argv);

    HostInterface hostInterface() const;
    void setHostInterface(HostInterface);

    void exec(XeScreen *first);
    bool isExecuting() const;
    void exit();

    XeScreen *screen() const;
    void push(XeScreen *);
    void pop();
    void swap(XeScreen *);

    XeWindow *window() const;

    bool hasDevice(const char *id) const;
    XeInputDevice *device(const char *id) const;

    XeUpdater *preUpdate() const;
    XeUpdater *postUpdate() const;

    int& argc() const;
    char **argv() const;

private:
    QStack<XeScreen*> m_screen;

    HostInterface m_host;
    bool m_executing;
    void *m_nativeWindow;
    void *m_nativeInputs;
    void *m_nativeScheduler;
    XeUpdater *m_preUpdate;
    XeUpdater *m_postUpdate;
    int& m_argc;
    char **m_argv;
};

extern XeKernel *xe_kernel;

// TODO doc comments yay
