
## Windowing

Xenon abstracts away the system's windowing system, exposing a few useful APIs:

* `isFullScreen()`, `toggleFullScreen()`, `setFullScreen()` to switch between windowed and fullscreen modes.
  Xenon currently does not support fullscreen exclusive mode on any platform.

* `title()`, `setTitle()` to get/set the title of the window (relevant only in windowed mode).

* `bounds()`, `setBounds()` to get/set the client bounds of the window.
  Note the client bounds do not include the chrome of the window (a window with client bounds of 800x600 is rendering to 800x600 pixels).
  By default, `setBounds()` also updates `glViewport()` to match. This can be disabled with an optional parameter to `setBounds`.

When the kernel is running, the application's current window can be accessed by calling

```cpp
xe_kernel->window()
```

