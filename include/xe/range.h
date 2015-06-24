
#pragma once

#include "xe/global.h"

/** Represents a continuous range of values with inclusive minimum
  * and maximum bounds
  */
template<typename T>
class XE_EXPORT XeRangeT
{
public:
    XeRangeT() : min(0), max(0) { }
    XeRangeT(T min, T max) : min(min), max(max) { }    

    T min;
    T max;

    bool contains(int val) const { return min <= val && val <= max; }
    bool contains(float val) const { return min <= val && val <= max; }

    T lerp(float val) const { return (T)(min + (max - min) * val); }
};

typedef XeRangeT<int> XeRange;
typedef XeRangeT<float> XeRangeF;

