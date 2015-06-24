
#pragma once

#include "xe/axisinput.h"
#include "xe/buttoninput.h"
#include "xe/inputdevice.h"

#include "window.h"

#include <QHash>
#include <QKeyEvent>
#include <QString>

class QtKeyboardButton : public XeButtonInput
{
public:
    QtKeyboardButton(const QString &);

    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    bool isDown() const;

    bool down;
    QString keyid;
};

class QtKeyboard : public XeInputDevice
{
public:
    QtKeyboard();

    QtWindow *window() const;
    void setWindow(QtWindow*);

    const char *id() const;
    const char *name() const;

    bool hasAxis(const char *id) const;
    bool hasButton(const char *id) const;

    void axes(QList<const char *> &out);

    void buttons(QList<const char *> &out);

    XeAxisInput *axis(const char *id) const;
    XeButtonInput *button(const char *id) const;

    void update(float);

private:
    QHash<QString, QtKeyboardButton *> m_buttons;
    QtWindow *m_window;

    friend class QtWindow;

    void keydown(QKeyEvent *);
    void keyup(QKeyEvent *);
};

