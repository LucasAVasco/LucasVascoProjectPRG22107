# Implementation

The game is implemented inC++ with the Qt framework. To build the game we use the [CMake](https://cmake.org/) build system. The compiler
used is [GCC](https://gcc.gnu.org/). Eventually, the [Qt Creator](https://www.qt.io/product/development-tools) IDE is used for the
development.

## Code quality

To format the code, we use the [clang-format](https://clang.llvm.org/docs/ClangFormat.html) formatter and an
[EditorConfig](https://editorconfig.org/) file.

## Source code

The source code and the building instructions are available at the [./code/](./code/) directory.

## Continues integration and deployment

The game us automatically built using a [Github workflow](https://docs.github.com/en/actions) available at
[../.github/workflows/build-and-release.yaml](../.github/workflows/build-and-release.yaml). This workflow is triggered at each push of a new
version (tag beginning with `v`) to the repository and generates a new release at the
[releases](https://github.com/LucasAVasco/LucasVascoProjectPRG22107/releases) page.

<div align="center">

[Retroceder](projeto.md) | [Início](analise.md)

</div>
