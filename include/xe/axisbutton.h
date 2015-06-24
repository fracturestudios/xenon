
#pragma once

#include "xe/axisinput.h"
#include "xe/buttoninput.h"
#include "xe/global.h"
#include "xe/range.h"

#include <QString>

/** A button input that wraps an axis inputs. The virtual button created from
  * the axis is down when the axis's value falls within a certain range
  */
class XE_EXPORT XeAxisButton : public XeButtonInput
{
public:
    XeAxisButton(XeAxisInput *child, const XeRangeF &active = XeRangeF(.5f, 1.f));

    /** Gets or sets the axis this button wraps */
    XeAxisInput *child() const;
    void setChild(XeAxisInput*);

    /** Gets or sets the range of axis values for which this button is 'down' */
    const XeRangeF &activationRange() const;
    void setActivationRange(const XeRangeF&);

    const char *id() const;
    const char *name() const;
    const char *deviceID() const;

    bool isDown() const;

private:
    XeAxisInput *m_axis;
    XeRangeF m_range;
    QString m_id, m_name;
};

