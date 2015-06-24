
#pragma once

#include "xe/global.h"
#include "xe/rect.h"

/** Allows manipulation of the game's window. While the kernel is running,
  * an instance of this object that can manipulate the game's window is
  * available using xe_kernel->window().
  */
class XE_EXPORT XeWindow
{
public:
    /** Gets the platform-specific handle for this window */
    virtual void *handle() const = 0;

    /** Gets or sets the text in this window's title bar */
    virtual const char *title() const = 0;
    virtual void setTitle(const char *) = 0;
    
    /** Gets or sets the client bounds of this window, in pixels.
      * The client bounds of a window do not include pixels dedicated to
      * the window's chrome.
      */
    virtual XeRect bounds() const = 0;
    virtual void setBounds(const XeRect &) = 0;

    /** Shows or hides this window */
    virtual void show() = 0;
    virtual void hide() = 0;

    /** Gets or sets the fullscreen state of this window */
    virtual bool isFullscreen() const = 0;
    virtual void setFullscreen(bool) = 0;
    virtual void toggleFullscreen() = 0;
};

