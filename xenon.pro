
QT += core gui opengl

TARGET = xenon
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3

DEFINES += XENON_LIBRARY

INCLUDEPATH += include
DEPENDPATH  += src/instrument src/input

SOURCES += src/instrument/tracetype.cpp \
           src/instrument/tracelogger.cpp \
           src/instrument/trace.cpp \
           src/instrument/filelogger.cpp \
           src/instrument/profiler.cpp \
           src/updater.cpp \
           src/input/buttoninput.cpp \
           src/input/axisinput.cpp \
           src/input/inputdevice.cpp \
           src/input/andbutton.cpp \
           src/input/orbutton.cpp \
           src/input/notbutton.cpp \
           src/input/axisbutton.cpp \
           src/input/buttonaxis.cpp \
           src/input/input.cpp \
           src/native/kernel.cpp \
           src/math/vector2.cpp \
           src/math/vector3.cpp \
           src/math/vector4.cpp \
           src/math/quaternion.cpp

HEADERS += include/xe/global.h \
           include/xe/config.h \
           include/xe/tracetype.h \
           include/xe/tracelogger.h \
           include/xe/trace.h \
           include/xe/filelogger.h \
           include/xe/profiler.h \
           include/xe/updatable.h \
           include/xe/updater.h \
           include/xe/rect.h \
           include/xe/window.h \
           include/xe/buttoninput.h \
           include/xe/axisinput.h \
           include/xe/inputdevice.h \
           include/xe/andbutton.h \
           include/xe/orbutton.h \
           include/xe/notbutton.h \
           include/xe/axisbutton.h \
           include/xe/buttonaxis.h \
           include/xe/input.h \
           include/xe/kernel.h \
           include/xe/vector2.h \
           include/xe/vector3.h \
           include/xe/vector4.h \ 
           include/xe/quaternion.h \
           include/xe/matrix.h \
           include/xe/vector.h

# XeKernel::HOST_QT native interface

HEADERS += src/native/qt/window.h \
           src/native/qt/scheduler.h \
           src/native/qt/mouse.h \
           src/native/qt/keyboard.h \
           src/native/qt/inputs.h \
           src/native/qt/init.h

SOURCES += src/native/qt/window.cpp \
           src/native/qt/scheduler.cpp \
           src/native/qt/mouse.cpp \
           src/native/qt/keyboard.cpp \
           src/native/qt/inputs.cpp \
           src/native/qt/init.cpp

