
## Instrumentation


Xenon helps you debug and profile your game.

### Trace Logging

The global `xe_trace` object records timestamped log entries.
The entries can be sent to implementations of `XeTraceTarget`.
Currently, there are `XeTraceTarget` implementations which send log lines lines to stderr and to a file.

You can use `xe_trace` in printf()-like and cout-like modes:

```cpp
xe_trace.warn("Important number: %d", some_number);
xe_trace.fatal("something was null!");

xe_trace.info << "Hello world!";
```

Messages are sorted by severity

* **Fatal**: Critical failure; crash imminent
* **Error**: Something happened that shouldn't have, but the game was able to recover from it
* **Warning**: Something that might be intentional but could be a mistake
* **Status**: The game is doing something of note (like loading a level)

The `xe_trace` object contains a member object for each severity level.

### Profiling

The `XeProfiler` object can be used for coarse-grained application profiling.
For example:

```cpp
XeProfiler samp;

samp.begin("AI");
my_process_ai();
samp.end("AI");

samp.begin("Collision Detection");
my_process_collisions();
samp.end("Collision Detection");

...
```

The data collected by this sampler can be easily dumped to `xe_trace` or rendered to the screen in real time.
Samplers have a default "Other" category encapsulating times when the sampler is not running.

