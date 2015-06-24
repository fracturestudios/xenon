
## XeKernel

The game is responsible for implementing a main() function.
Inside main(), the game initializes a Kernel object and then calls into it, passing in the first screen to be executed.

The `XeKernel` object is responsible for creating application windows, initializing an OpenGL context, and setting up input devices.
Once this is complete, the kernel becomes the global `xe_kernel` object and begins calling into the currently active `XeScreen`'s `update()` and `render()` functions at regular intervals. 

The kernel owns a few important objects, including

* The application's window
* The application's input devices
* The `XeScreen` stack

An example main function:

```cpp
int main(int argc, const char *argv[])
{
    XeKernel kernel;

    my_startup_chores();

    kernel.setHostInterface(XeKernel::HOST_QT); // Use Qt for windowing / input
    kernel.exec(new LoadingScreen(new MainMenuScreen()));

    my_shutdown_chores();
}
```

## Native Interface

`XeKernel` relies on platform support to handle things like creating a window, getting an OpenGL context, and receiving input.
This platform support is factored into a 'host interface', chosen by the caller in `XeKernel::setHostInterface`.
Currently there is only one host interface, which uses Qt to run on Windows, Mac and Linux.

### Adding Support for a New Platform

To add a new native/host interface

* (suggested) Add a subfolder to `src/native` to place your headers and sources
* Implement `XeWindow`, `XeInputs`, `XeScheduler` (the latter are private to the engine, their headers are defined in `src/native`)
* Implement a `XeKernelInit` function to initialize the above in the necessary order
* Add a value to the `XeKernel::HostInterface` enumeration
* Add your function to `XeKernelInitializers` (in `kernel.cpp`).
  Each value in this array is indexed by the `(int)` value of the corresponding value in `XeKernel::HostInterface`. 

Then you should be able to run Xenon off of your new host interface by specifying your enum value in a call to `setHostInterface()`.
Note you must make this call before `exec`ing your kernel.

