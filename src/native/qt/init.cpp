
#include "init.h"
#include "inputs.h"
#include "scheduler.h"
#include "window.h"

#include "xe/kernel.h"

#include <QApplication>

void QtHostInit(XeKernel *kernel, XeWindow **outWindow, XeInputs **outInputs, XeScheduler **outScheduler)
{
    new QApplication(kernel->argc(), kernel->argv());

    QtWindow *win = new QtWindow();
    QtScheduler *sched = new QtScheduler();
    QtMouse *mouse = new QtMouse();
    QtKeyboard *keyboard = new QtKeyboard();
    QtInputs *inputs = new QtInputs();

    win->setSched(sched);
    win->setMouse(mouse);
    win->setKeyboard(keyboard);
    
    mouse->setWindow(win);
    keyboard->setWindow(win);

    inputs->setMouse(mouse);
    inputs->setKeyboard(keyboard);

    *outWindow = win;
    *outInputs = inputs;
    *outScheduler = sched;

    win->show();
}

