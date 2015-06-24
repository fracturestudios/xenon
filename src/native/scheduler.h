
#pragma once

/** A callback from the scheduler to the kernel
  * @param dt The number of seconds that have passed since the last render/tick
  * @param opaque The argument supplied when the callback was first set
  *               Use to store user-specific data
  */
typedef void (*XeSchedulerCallback)(float dt, void *opaque);

/** Abstract base for an object that generates update/render events.
  * Objects implementing this interface are consumed by the kernel based on
  * which host interface was selected at kernel startup. The kernel uses
  * these callbacks to update and render the current screen.
  */
class XeScheduler
{
public:
    /** Registers a callback that will be called on every update tick.
      * XeKernel's callback for this function calls update() on the current XeScreen
      * @param f The callback function to call
      * @param tag The opaque argument to pass to the function
      */
    virtual void setUpdateCallback(XeSchedulerCallback f, void *arg) = 0;

    /** Registers a callback that will be called on every render tick.
      * XeKernel's callback for this function calls render() on the current XeScreen
      * @param f The callback function to call
      * @param tag The opaque argument to pass to the function
      */
    virtual void setRenderCallback(XeSchedulerCallback f, void *arg) = 0;

    /** Allows the scheduler to set up the next update/render callback calls.
      * On some platforms, this method just calls the update and render callbacks
      * On others, it might e.g. process an OS event queue.
      * The kernel calls this function in a while loop until it is finished executing.
      */
    virtual void tick() = 0;
};

