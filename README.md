What is inside
=============================

key-common
----------

Should contains definitions required for cross-platform support.

Right now it contains types.h file which has cross-platform definitions of integer types.
- int32_t 32 bit integer
- uint16_t unsigned 16 bit integer

key-math
--------

Vector, Matrix aritmetic.

Contains classes to create N-dimensional vectors and do operations with them.

key-random
----------
Contains algorithms used to generate random or pseudo-random stuff. 
Now it contains almost finished perlin noise implementation.

key-space
--------
Space partitioning clases

noise-01
--------

Executable example that fills your screen with static noise

noise-02
--------
A demo of permutation-based algorithm that generates same thing as perlin noise but not smoothed

noise-03
--------
3D perlin noise example

COMPILATION
===========

Create a dir for this project:

> /key-escape

Here, create another dir inside:

> /key-escape/project

Set-up git and get src with git. put it into:

> /key-escape/project/src

Download CMake and install it http://www.cmake.org/cmake/resources/software.html

Run its GUI.

In "where is the source code" field write path to:

> /key-escape/project/src

in "where to build binaries" write:

> /key-escape/build-x86

Click "Configure" this will let you to choose your project generator.
Select Visual Studio 32 bit from the list.

When you click "Generate", the project files will be generated in the dir you specified for 32-bit build.

For this project, you will need to click "advanced" view in CMake and replace all /MD and /MDd C and CXX flags to /MT and /MTd

Once you re-generate the project files, you can open this project in visual studio and build it.

You also will need to put third party libraries and headers into /key-escape/project folder:

- /key-escape/project/third-party-include (header files)
- /key-escape/project/third-party-lib (compiled binaries)

To save you the trouble of compiling I will just zip these two into project-third-party.7z and will send them to you :)
