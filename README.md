Things to know to get started
=============================

[21:18:20] Nerijus: https://github.com/Nercury/key-escape
[21:19:01] Davide Vitelaru: noticed the repo
[21:19:10] Nerijus: key-common: should not contain anything. right now it contains types.h file which has cross-platform definitions of integer types
[21:19:23] Nerijus: int32_t 32 bit integer
[21:19:33] Nerijus: uint16_t unsigned 16 bit integer
[21:20:07] Nerijus: and so on, we should not use "int" because it has different number of bytes when project is compiled for 32-bit versus 64-bits
[21:20:25] Davide Vitelaru: can we do
[21:20:26] Nerijus: key-events: an experiment, skip it
[21:20:32] Davide Vitelaru: #define int int32_t
[21:20:33] Davide Vitelaru: ?
[21:20:36] Davide Vitelaru: or something like that
[21:20:38] Nerijus: um, open it
[21:20:38] Davide Vitelaru: and still use int
[21:20:44] Nerijus: no
[21:20:53] Nerijus: int is built-in
[21:21:16] Nerijus: anyway, this is the best practice, you will find other libraries doing the same
[21:21:36] Nerijus: key-math: vector, matrix aritmetic
[21:21:59] Nerijus: contains classes to create N-dimensional vectors and do operations with them
[21:22:31] Nerijus: key-random: contains algorithms used to generate random or pseudo-random stuff
[21:22:39] Nerijus: now it contains almost finished perlin noise
[21:23:20] Nerijus: key-space: skip it (it will contains space partitioning clases)
[21:23:39] Nerijus: noise-01 executable example that fills your screen with static noise
[21:24:18] Nerijus: noise02: demo of permutation-based algorithm that generates same thing as perlin noise but not smoothed
[21:24:33] Nerijus: noise-03: 3D perlin noise example
[21:24:52] Nerijus: all three should work now :)
[21:25:21] Nerijus: COMPILATION
[21:26:00] Nerijus: create a dir for this project:
/key-escape
[21:26:27] Nerijus: here, create another dir inside
/key-escape/project
[21:27:06] Nerijus: set-up git and get src with git. put it into
/key-escape/project/src
[21:27:41] Nerijus: download CMake and install it http://www.cmake.org/cmake/resources/software.html
[21:27:54] Nerijus: run its GUI
[21:29:06] Nerijus: in "where is the source code" field write path to
/key-escape/project/src
in "where to build binaries" write
/key-escape/build-x86
[21:29:51] Nerijus: click "Configure" this will let you to choose your project generator.
[21:30:12] Nerijus: select Visual Studio 32 bit from the list.
[21:31:06] Nerijus: when you click "Generate", the project files will be generated in the dir you specified for 32-bit build.
[21:31:45] Davide Vitelaru: we need to save this convo :D
[21:33:34] Nerijus: for this project, you will need to click "advanced" view in CMake and replace all /MD and /MDd C and CXX flags to /MT and /MTd
[21:34:17] Nerijus: once you re-generate the project files, you can open this project in visual studio and build it
[21:35:32] Nerijus: now, /key-escape/project folder should contain two more folders for external dependencies
[21:36:10] Nerijus: they are 
/key-escape/project/third-party-include
/key-escape/project/third-party-lib
[21:36:19] Nerijus: include contains header files for them
[21:36:28] Nerijus: while lib contains compiled binaries
[21:36:57] Nerijus: to save you the trouble of compiling i will just zip these two and send to you :)
[21:37:40] Nerijus: ok, i need to save this conversation now
