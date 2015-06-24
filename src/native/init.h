
#pragma once

class XeKernel;
class XeWindow;
class XeInputs;
class XeScheduler;

/** Initializes platform-dependent kernel objects.
  * Each kernel host interface implements a XeKernelInit function for the
  * kernel to call at the beginning of exec()
  * @param kernel A pointer to the initializing kernel that called this function
  * @param win Receives the window, which should already be visible
  * @param inputs Receives an input device enumerator with a list of input
  *               devices supported by the host interface
  * @param sched Recieves the scheduler object that will be used to drive
  *              the update and render loops
  */
typedef void (*XeKernelInit)(XeKernel *kernel, XeWindow **win, XeInputs **inputs, XeScheduler **sched);

