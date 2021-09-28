# Introduction

This programming project provides unit tests for the `sc::list<>` class. A description of the assignment can be found [**here**](docs/projeto_ED_list.pdf).

# Organization

The folders and files of this project are the following:

* `source/tmanager_lib`: This is the library that provides supports for the unit tests. Do not change or delete this folder.
* `source/tests`: This folder has the file `main.cpp` that contains all the tests. You might want to change this file and comment out some of the tests while you have not finished all the `sc::vector`'s methods.
* `source/include`: This is the folder in which you should add the `vector.h` file with your solution (i.e. the implementation of the class `sc::vector`).
* `source/CMakeLists.txt: The cmake script file.
* `README.md`: This file.
* `docs`: This folder has a pdf describing the vector project.

# Compiling

This project may be compiled with [CMake](https://cmake.org). CMake is an open-source, cross-platform family of tools designed to build, test and package software. Basically, cmake reads a script (`CMakeLists.txt`) with meta-information on the project and **creates a Makefile automatically**, tailored to your system configuration.
After that, you may run the `make` command, as usual.
Alternatively, the same script might be used to create Xcode projects, Ninja, or Microsoft Visual Studio projects, for instance.

CMake supports **out-of-source** build. This means the _source code_ is stored in **one** folder and the _generated executable files_ should be stored in **another** folder: project should never mix-up the source tree with the build tree.

In particular, this project creates a single **target** (executable), called `run_tests`.

But don't worry, they are already set up in the `CMakeLists.txt` script.

To compile this project with [cmake](https://cmake.org) follow these steps (from the root folder):

1. `cmake -S source -B build`:  asks cmake to create the build directory and generate the Unix Makefile based on the script found in `source/CMakeLists.txt`, on the current level.
3. `cmake --build build`: triggers the compiling process that creates both targets (executable).D inside `build`.

The executable is created inside the `build` directory.

For further details, please refer to the [cmake documentation website](https://cmake.org/cmake/help/v3.14/manual/cmake.1.html).

**NOTE** however, that this project **may compile at first** but the tests will most certainly fail.

We have in this project two batches of tests: 24 unit tests for the `sc::list` class, and 9 unit tests for the `sc::list::iterator` class, and 22 tests for the utility operations. You should try to get passed all these tests.

## Compiling withou cmake

If you wish to compile this project without the cmake, create the `build` folder manually (`mkdir build`), then try to run the command below from the source folder:

```
g++ -Wall -std=c++11 -I source/include -I source/tmanager_lib source/tests/main.cpp source/tmanager_lib/test_manager.cpp -o build/run_tests
```

# Running

From the project's root folder, run as usual (assuming `$` is the terminal prompt):

```
$ ./build/run_tests
```

# Authorship

Program developed by Selan (<selan@dimap.ufrn.br>), 2021.1

&copy; DIMAp/UFRN 2016-2021.

