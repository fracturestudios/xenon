
#pragma once

#include "xe/buttoninput.h"
#include "xe/global.h"

#include <QList>
#include <QString>

/** A button whose isDown() value is true if and only if one of its child
  * XeButtonInputs is also down. Acts like an OR gate for
  * XeButtonInput::isDown().
  */
class XE_EXPORT XeOrButton : XeButtonInput
{
public:
    void attach(XeButtonInput *);
    void detach(XeButtonInput *);
    bool isAttached(XeButtonInput *) const;

    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    bool isDown() const;

private:
    QList<XeButtonInput *> m_children;
    QString m_id;
    QString m_name;

    void rename();
};

