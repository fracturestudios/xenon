
## Screens

A `Screen` is an object with its own self-contained update/draw loop.
The kernel only ever runs one `Screen` at a time.

The kernel supplies a stack of `Screen`s, the top of which is the currently running screen.
This stack can be modified via push, pop and swap operations, which place a new screen on the stack, remove the top screen from the stack, and replace the top screen on the stack respectively.

Pushing a screen onto the stack is an elegant way to save the state of the current screen without needing the two screen objects to cooperate with each other.
For example, the main gameplay screen could call

```cpp
xe_kernel->screens.push(new PauseMenu());
```

When the user selects "Continue" in the pause menu, the menu can just call

```cpp
xe_kernel->screens.pop();
```

If the user selects "Main Menu", the PauseMenu screen could alternately do

```cpp
xe_kernel->screens.pop(); // Remove self from the stack
xe_kernel->screens.swap(new MainMenu()); // Remove the gameplay screen and 
                                         // switch to the main menu screen
```

Note that modifying the screen stack has no effect until the current `update()` and/or `render()` call returns.

## Transitions

Each `Screen` has a `load()` and an `unload()` function.

* The kernel calls `load()` before calling `update()` or `render()` for the first time. 
* The kernel calls `unload()` once no more calls to `update()` or `render()` are possible.

Note that `load()` and `unload()` are called synchronously within the update/draw loop, and thus should work relatively quickly.
If your `Screen` needs to load large assets or do extensive processing, consider implementing a loading screen that keeps the app responsive while the desired `Screen`'s contents are loaded on a separate thread.

`load()` and `unload()` are suitable for, e.g., initializing OpenGL shaders and other small pieces of content.

