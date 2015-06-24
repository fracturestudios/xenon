
#pragma once

/** If enabled, source files are compiled without import/export attributes.
  * Useful if you want to compile xenon into your application instead of using
  * it as a shared/static library
  */
#define XE_NOLIB 1

/** If disabled, all XeProfiler begin/end calls become no-ops */
#define XE_PROFILING 1

