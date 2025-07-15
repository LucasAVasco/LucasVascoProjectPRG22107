# Instructions for compilation and system execution

You must have a C++ compiler, CMake and the Qt framework installed (including development files for Qt).

Setup command:

```sh
cmake --preset release
```

Build command:

```sh
cmake --build build/
```

Run the executable:

```sh
./build/space-invaders
```

## Unit tests configuration

The unit tests are manager by [GoogleTest](https://github.com/google/googletest). The CMake configuration automatically installs it.

Setup command:

```sh
cmake --preset test-only
```

Build command:

```sh
cmake --build build
```

Run the tests:

```sh
ctest --test-dir build --output-on-failure
```
