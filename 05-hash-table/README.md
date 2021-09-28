# Introduction

This programming project provides unit tests for the `sc::HashTbl<>` class.

# Organization

The folders and files of this project are the following:

* `source/driver`: This folder has two source files, (1) `driver_ht.cpp` that demonstrates the hash table in action for the `Account` problem described in the assignment PDF, and; (2) `account.cpp` that contains the implementation of the `Account` class.
* `source/test`: This folder has the file `main.cpp` that contains all the tests. Note that the tests were developed with [**Googletest**](https://github.com/google/googletest).
* `source/include`: This is the folder contains 2 files, (1) `hashtbl.h` with the declaration of the `HashTbl` class, (2) `hashtbl.inl` that should contain the implementation `HasTbl`'s methods.
* `source/CMakeLists.txt`: The cmake script file.
* `README.md`: This file.
* `docs`: This folder has a pdf describing the list project.

# Compiling

This project may be compiled with [CMake](https://cmake.org). CMake is an open-source, cross-platform family of tools designed to build, test and package software. Basically, cmake reads a script (`CMakeLists.txt`) with meta-information on the project and **creates a Makefile automatically**, tailored to your system configuration.
After that, you may run the `make` command, as usual.
Alternatively, the same script might be used to create Xcode projects, Ninja, or Microsoft Visual Studio projects, for instance.

CMake supports **out-of-source** build. This means the _source code_ is stored in **one** folder and the _generated executable files_ should be stored in **another** folder: project should never mix-up the source tree with the build tree.

In particular, this project creates two  **targets** (executable), called `run_tests` and `driver_hash`. The first runs the tests whereas the second demonstrates the application of a hash table to a specific problem.

But don't worry, they are already set up in the `CMakeLists.txt` script.

To compile this project with [cmake](https://cmake.org) follow these steps (from the root folder):

1. `cmake -S source -B build`:  asks cmake to create the build directory and generate the Unix Makefile based on the script found in `source/CMakeLists.txt`, on the current level.
3. `cmake --build build`: triggers the compiling process that creates both targets (executable).D inside `build`.

The executable is created inside the `build` directory.

For further details, please refer to the [cmake documentation website](https://cmake.org/cmake/help/v3.14/manual/cmake.1.html).

**NOTE** however, that this project may compile but it will probably generate a **seg fault** since the hash table methods are "empty".

We have in this project a single batch of 21 tests.

# Dependencies

You must install the **Googletest** Library, which you may clone from [here](https://github.com/google/googletest).
After cloning the project, you will need to compile it and install it in your system or locally.

If you need, you may find a good **Googletest** tutorial [here](https://google.github.io/googletest/primer.html), although it would be probably uncessary to access this documentation since the tests have already been coded for you. You just need to install the library and compile the project.

The `CMakeLists.txt` automatically looks for the location of the **Googletest** libraries in your system. If you decide to install **Googletest** locally you will need to change the cmake configuration file to indicate where you've installed the **Googletest** library (path).

# Running

From the project's root folder, run as usual (assuming `$` is the terminal prompt):

```
$ ./build/run_tests
```
and for the driver, type in

```
$ ./build/driver_hash
```

You may want to compare the output the driver program with my output, which can be found [here](docs/output_driver.txt).

# Authorship

Program developed by Selan (<selan@dimap.ufrn.br>), 2021.1

&copy; DIMAp/UFRN 2016-2021.

