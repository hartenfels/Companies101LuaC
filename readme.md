Implementation for [101 Companies](http://101companies.org/), see http://101companies.org/wiki/Contribution:c for details.

# Requirements
This application manages its build process using [CMake](http://www.cmake.org/). It also requires a C11 capable compiler (e.g. GCC or Clang) and [Lua 5.1](http://www.lua.org/).

# Unix

## Building
Open a terminal in the project directory and run the following commands:

    mkdir build
    cd build
    cmake ..
    make

This will find the required library and compiler information, build an executable, a shared library and tests using that shared library in the build folder. To run the executable, use `./c101`.

## Testing
Testing uses CTest from CMake.

After running `make` and building everything, run `make test` to run CTest.

# Windows
CMake comes with support for Visual Studio and the contribution is written in standard C11, so in theory it should run on Windows with no modification. How exactly one builds anything in Visual Studio has remained a mystery to me though, so I cannot provide any further instructions.

There is also MinGW and Cygwin to emulate a Unix environment, in which case you can follow the Unix instructions above.

