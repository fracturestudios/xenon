
## Input

Xenon provides two types of player input:

* Buttons represent boolean values: they can be down or up. 
* Axes represent floating-point values, ranging from -1 to 1. Their values can easily be linearly scaled.

Examples:

```cpp
player.sprinting = my_button.isDown();
player.velocity += player.forward * my_axis.value();
```

### Up/Down vs Pressed/Released

Buttons have a notion of being 'pressed' or 'released', which is different from being 'up' or 'down'.
A button is down for all update ticks during which the player is holding the button down; however, the button is only pressed for the first update tick the button is held down.
This is useful for fire-once input responses, like moving up or down in a menu.

```cpp
xe_trace.info << my_button.isDown() << " " << my_button.isPressed();
// First tick: "True True"
// Second tick: "True False"
```

### Special Buttons

Xenon provides button and axis types that let one masquerade as the other.

* `AxisButton` wraps an axis and acts like a button.
  The 'button' is pressed when the value of the axis falls within a certain range.

* `ButtonAxis` wraps one or more buttons and acts like an axis.
  Each source button produces an axis value (which changes whether the button is down or up).
  The value of the 'axis' is the sum of the buttons' values.

Xenon provides buttons that act like AND, OR and NOT gates

* `AndButton` wraps one or more buttons and is down when all of the buttons are down.
  Useful for implementing key combos, especially fire-once combos (e.g. Alt+Enter for fullscreen).

* `OrButton` wraps one or more buttons and is down when at least one of the buttons is down.
  This allows two different key presses to do the same thing without special cases in your game code.

* `NotButton` wraps a single button is down when the button is up, and vice versa.

Since these special inputs implement the common axis/button interfaces, you can compose them to create flexible input hierarchies.

### Input Maps

Input maps allow you to reference buttons and axes by their logical meaning rather than their device/input ID.
This makes it easy to change your game's control scheme on-the-fly.

The globally active input map is `xe_input`.

```cpp
xe_input.b.map("sprint", "Keyboard", "LeftShift");
xe_input.b.map("menu_select", new XeOrButton(xe_input.device("Keyboard").button("Enter"),
                                             xe_input.device("Keyboard").button("Space")));
xe_input.a.map("look_y", "Mouse", "CursorDY");

// ...

player.sprinting = xe_input.b["sprint"].isDown();

if (xe_input.isPressed("menu_select")) {
    current_menu_item->performAction();
}

camera.pitch += xe_input.a["look_y"].value();
```

Avoid caching the buttons/axes returned by `xe_input` for more than a single frame.
If you retrieve the inputs from the input map every frame, the player can change the keymap while the game is running.

