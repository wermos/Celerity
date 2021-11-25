# Tracer [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![](https://tokei.rs/b1/github/wermos/Tracer)](https://tokei.rs/b1/github/wermos/Tracer) [![Windows](https://github.com/wermos/Tracer/actions/workflows/windows.yml/badge.svg)](https://github.com/wermos/Tracer/actions/workflows/windows.yml) [![Linux GCC](https://github.com/wermos/Tracer/actions/workflows/linux-gcc.yml/badge.svg)](https://github.com/wermos/Tracer/actions/workflows/linux-gcc.yml) [![Linux Clang](https://github.com/wermos/Tracer/actions/workflows/linux-clang.yml/badge.svg)](https://github.com/wermos/Tracer/actions/workflows/linux-clang.yml)
A ray-tracing engine, written using [this book](https://raytracing.github.io/books/RayTracingInOneWeekend.html) for inspiration and the theory behind the ideas.

# Building the Project

## Pre-Requisites

1. A C++20 compliant compiler
    * GCC >= 10 or Clang >= 10 or MSVC >= 19.30 should do.
    * In particular, any compiler with support for C++20 Concepts (as of now) will do.
2. CMake

## Instructions
1. Clone the repository.
    * You can clone the repo by running `git clone https://github.com/wermos/Tracer.git`.
2. Run CMake on the repository.
    * Run `cmake -S. -Bbuild -G[generator]`.
        - If you are on Linux, then you can ignore the `-G` flag (as in, not use it at all) or just use `-G"Unix Makefiles"`. (Since this is the default, both variants have the same behavior.)
		- If you are on Windows (with Visual Studio, presumably), you can use `"Ninja"` in place of `[generator]` or `"Visual Studio 16 2019"`.
		- For more help, you can visit the [CMake docs](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).
	* To pass in a specific build type, you can append `-DCMAKE_BUILD_TYPE=[type]` to the above command. The choices for `[type]` are `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`, and `Profile`.
	    - All the build types except for `Profile` are available for all CMake projects by default.
		- The `Profile` build type is simply a release build but with instrumentation-related code packaged along with it. This allows for benchmarking the code.
3. Run the executable.
    * The executable will be in `build/Tracer/`. The name of the executable `RayTracer` (Linux) or `RayTrace.exe` (Windows).

# Benchmarks
The benchmarks for the code are stored in the current working directory from where the executable is run in a file whose default name is `results.json`.

To see a nice visual depiction of all the profiling data, one can simply upload the output `.json` file into [Perfetto UI](https://ui.perfetto.dev/).
