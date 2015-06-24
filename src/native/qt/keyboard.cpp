
#include "keyboard.h"

#include <QKeyEvent>

static QHash<QString, QString> idToName;
static QHash<int, QString> qtToId;
static const char *keyboardDeviceID = "Keyboard";
static const char *keyboardDeviceName = "Keyboard";

QtKeyboardButton::QtKeyboardButton(const QString &id) : down(false), keyid(id) { }

const char *QtKeyboardButton::id() const
{
    return keyid.toUtf8().data();
}

const char *QtKeyboardButton::name() const
{
    return idToName[keyid].toUtf8().data();
}

const char *QtKeyboardButton::deviceID() const
{
    return keyboardDeviceID;
}

bool QtKeyboardButton::isDown() const
{
    return down;
}

static QtKeyboardButton *defkey(const QString &id, const QString &name, int qt)
{
    QtKeyboardButton *b = new QtKeyboardButton(id);

    idToName[id] = name;
    qtToId[qt] = id;

    return b;
}

QtKeyboard::QtKeyboard() : m_window(0)
{
    // A-Z
    for (int i = 0; i < 26; ++i)
    {
        char letter = 'A' + i;
        QString id(letter);
        m_buttons[id] = defkey(id, id, Qt::Key_A + i);
    }
    
    // 0-9
    for (int i = 0; i <= 10; ++i)
    {
        char num = '0' + i;
        QString id(num);
        m_buttons[id] = defkey(id, id, Qt::Key_0 + i);
    }

    // F1 -> F12
    for (int i = 0; i < 12; ++i)
    {
        QString id = "F";
        id += QString::number(i + 1);
        m_buttons[id] = defkey(id, id, Qt::Key_F1 + i);
    }

    // Misc
#if __APPLE__
    m_buttons["Control"] = defkey("Control", "Command", Qt::Key_Control);
    m_buttons["Meta"] = defkey("Meta", "Control", Qt::Key_Meta);
#else
    m_buttons["Control"] = defkey("Control", "Control", Qt::Key_Control);
    m_buttons["Meta"] = defkey("Meta", "Control", Qt::Key_Meta);
#endif
    m_buttons["Alt"] = defkey("Alt", "Alt", Qt::Key_Alt);
    m_buttons["Shift"] = defkey("Shift", "Shift", Qt::Key_Shift);
    m_buttons["Tab"] = defkey("Tab", "Tab", Qt::Key_Tab);
    m_buttons["Enter"] = defkey("Enter", "Enter", Qt::Key_Return);
    m_buttons["Backspace"] = defkey("Backspace", "Backspace", Qt::Key_Backspace);
    m_buttons["Escape"] = defkey("Escape", "Escape", Qt::Key_Escape);
    m_buttons["Space"] = defkey("Space", "Space", Qt::Key_Space);
    m_buttons["Left"] = defkey("Left", "Left Arrow", Qt::Key_Left);
    m_buttons["Right"] = defkey("Right", "Right Arrow", Qt::Key_Right);
    m_buttons["Up"] = defkey("Up", "Up Arrow", Qt::Key_Up);
    m_buttons["Down"] = defkey("Down", "Down Arrow", Qt::Key_Down);
}

QtWindow *QtKeyboard::window() const
{
    return m_window;
}

void QtKeyboard::setWindow(QtWindow *w)
{
    m_window = w;
}

const char *QtKeyboard::id() const
{
    return keyboardDeviceID;
}

const char *QtKeyboard::name() const
{
    return keyboardDeviceName;
}

bool QtKeyboard::hasAxis(const char *) const
{
    return false;
}

void QtKeyboard::axes(QList<const char *> &) { }

XeAxisInput *QtKeyboard::axis(const char *) const
{
    return 0;
}

bool QtKeyboard::hasButton(const char *id) const
{
    return m_buttons.contains(id);
}

void QtKeyboard::buttons(QList<const char *> &out)
{
    QHashIterator<QString, QtKeyboardButton*> it(m_buttons);
    while (it.hasNext())
        out.append(it.next().key().toUtf8().data());
}

XeButtonInput *QtKeyboard::button(const char *id) const
{
    return m_buttons[id];
}

void QtKeyboard::update(float dt)
{
    QHashIterator<QString, QtKeyboardButton*> it(m_buttons);
    while (it.hasNext())
        it.next().value()->update(dt);
}

void QtKeyboard::keydown(QKeyEvent *ev)
{
    if (qtToId.contains(ev->key()))
        m_buttons[qtToId[ev->key()]]->down = true;
}

void QtKeyboard::keyup(QKeyEvent *ev)
{
    if (qtToId.contains(ev->key()))
        m_buttons[qtToId[ev->key()]]->down = false;
}

