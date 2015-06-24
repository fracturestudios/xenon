
#pragma once

#include "xe/buttoninput.h"
#include "xe/global.h"

#include <QString>

/** A button whose isDown() is true if and only if its child's isDown()
  * value is false. Acts like a NOT gate for XeButtonInput::isDown().
  */
class XE_EXPORT XeNotButton : public XeButtonInput
{
public:
    XeNotButton();
    XeNotButton(XeButtonInput *child);

    XeButtonInput *child() const;
    void setChild(XeButtonInput *);

    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    bool isDown() const;

private:
    XeButtonInput *m_child;
    QString m_id;
    QString m_name;
};

