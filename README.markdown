
## Xenon

Xenon is lightweight infrastructure for writing a game in C++ using OpenGL.

### Features

Xenon currently supports the following features

* Cross-platform (tested on Windows, OS X, Linux)
* Windowing support
* Graphics initializatation
* Input handling and compositing
* Game 'screen' state machine

In the future, Xenon will also be extended to support

* Asset caching
* Texture management
* Rigid-body physics and collision detection

## Compiling

### Prerequisites

#### Qt 5.x

Xenon currently uses [Qt5](http://qt.io) for cross-platform windowing 
support, although this is abstracted away from you when you use Xenon.
To use Xenon, you'll need to set up Qt5 on your machine.
You'll also need to make sure you have `qmake` in your `PATH`.

#### GLEW

To ease the process of using the latest OpenGL versions available on each
respective platform, Xenon relies on 
[GLEW](https://github.com/nigels-com/glew).

### Building

Once the prerequisites are set up and working correctly, all you need
to build xenon is to run

    qmake && make

The result will be either `libxenon.a` or `xenon.lib`, depending on your
host platform.

### Linking to Xenon

To link to xenon, point your include path to the `include/` directory 
in this repository, and point your linker to the `libxenon.a` or 
`xenon.lib` you compiled from this repository.

Since Xenon is a static library, you'll also need to make sure the project
that links to Xenon also links to the prerequisites (Qt 5.x and GLEW).

