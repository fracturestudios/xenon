
#pragma once

#include "xe/axisinput.h"
#include "xe/buttoninput.h"
#include "xe/global.h"

#include <QList>
#include <QString>

/** An axis input that wraps button inputs. The value of the virtual axis
  * is the sum of the values associated with each child button. The value
  * associated with each child button changes whether the button is up
  * or down.
  *
  * For example, a forward/backward walk axis might have the following children:
  * - Keyboard.W, value when up: 0, value when down: 1
  * - Keyboard.S, vlaue when up: 0, value when down: -1
  */
class XE_EXPORT XeButtonAxis : public XeAxisInput
{
public:
    /** Attachs a button to this axis
      * @param button The button to attach
      * @param upval The value produced by the button when it is not being held down
      * @param downval The value produced by the button when it is being held down
      */
    void attach(XeButtonInput *button, float upval, float downval);
    /** Detaches a button from this axis */
    void detach(XeButtonInput *button);
    /** Gets a value indicating whether a button is attached to this axis */
    bool isAttached(XeButtonInput *) const;

    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    float value() const;

private:
    struct ButtonValue
    {
        XeButtonInput *button;
        float upval;
        float downval;

        ButtonValue(XeButtonInput *b, float up, float down) : button(b), upval(up), downval(down) { }
    };

    QList<ButtonValue> m_buttons;
    QString m_id, m_name;
};

