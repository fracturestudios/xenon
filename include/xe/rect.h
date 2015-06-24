
#pragma once

#include "xe/global.h"

/** Represents a two-dimensional axis-aligned rectangle */
template <typename T> 
class XE_EXPORT XeRectT
{
public:
    XeRectT() : x(0), y(0), width(0), height(0) { }
    XeRectT(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) { }

    T x;
    T y;
    T width;
    T height;

    T top() const { return y; }
    void setTop(T t) { y = t; }

    T bottom() const { return y + height; }
    void setBottom(T t) { height = t - y; }

    T left() const { return x; }
    void setLeft(T t) { x = t; }

    T right() const { return x + width; }
    void setRight(T t) { width = t - x; }
};

typedef XeRectT<int> XeRect;
typedef XeRectT<float> XeRectF;

