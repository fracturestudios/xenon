
#pragma once

#include "xe/global.h"
#include "xe/updatable.h"

/** Abstract base for a game screen.
  * Screens implement the required update/draw functionality for a
  * distinct portion of the game. 
  */
class XE_EXPORT XeScreen : XeUpdatable
{
public:
    /** Does any quick initialization needed by this screen object.
      * This method is guaranteed to be called before the first time
      * update() or render() is called. 
      * Since this method is called synchronously in the game loop,
      * it should not load large assets or do long compuation. If
      * you need to do this, consider implementing a loading screen.
      */
    virtual void load() = 0;
    /** Unloads assets in use by this screen that are no longer needed.
      * This method is guaranteed to be called only after update() and
      * render() have been called for the last time.
      */
    virtual void unload() = 0;

    /** Performs per-tick game logic
      * @param dt The amount of time that has elapsed, in partial seconds
      */
    virtual void update(float dt) = 0;
    /** Draws the visuals for this screen
      * @param dt The amount of time that has elapsed, in partial seconds
      */
    virtual void render(float dt) = 0;
};

