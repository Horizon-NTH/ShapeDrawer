# ShapeDrawer

[![Release](https://img.shields.io/badge/Release-v1.0-blueviolet)](https://github.com/Horizon-NTH/ShapeDrawer/releases)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)](https://en.wikipedia.org/wiki/C++)
[![Licence](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

![ShapeDrawer's Logo](assets/textures/ShapeDrawer.png)

## Introduction

**ShapeDrawer** is a primitive shapes rendering application.  
With just a few clicks or simple commands, you can create basic shapes such as circles, rectangles, triangles, and lines. Additionally, you can easily import shape files and save them to enhance the creation of your shapes.

## Installation Instructions

> You can also simply install a pre-built version [here](https://github.com/Horizon-NTH/ShapeDrawer/releases).

### Get Source Code

You first need to clone the [repository](https://github.com/Horizon-NTH/ShapeDrawer). Make sure to use [git](https://git-scm.com) and don't forget to include `--recurse-submodules` when cloning.

```bash
git clone https://github.com/Horizon-NTH/ShapeDrawer --recurse-submodules
```

You will now able to choose between [script](#script-installation) or [manual](#manual-installation) installation

- ### Script Installation

  Use the [`install.sh`](https://github.com/Horizon-NTH/ShapeDrawer/blob/master/install.sh) script to compile the executable. You can choose to erase build files by adding `-e` / `--erase`.

  ```bash
  ./install.sh --erase
  ```

- ### Manual Installation

  #### Create Build Environment

  Ensure you have [CMake](https://cmake.org/) installed. Generate the build environment using CMake. 

  ```bash
  cd ShapeDrawer
  mkdir build && cd build
  cmake ..
  ```

  #### Build

  - ##### CMake

    Build directly using CMake:

    ```bash
    cmake --build .
    ```

    This command will create all the executable in the main folder.

  - ##### Microsoft Visual Studio

    Alternatively, you can use [Microsoft Visual Studio](https://visualstudio.microsoft.com/) to launch the project and build it. Open the `shapedrawer.sln` file with Microsoft Visual Studio.

## Usage

To learn how to use this application, please refer to the [wiki](https://github.com/Horizon-NTH/ShapeDrawer/wiki).

## Dependencies

* **HorizonGUI**

    The code relies on [HorizonGUI](https://github.com/Horizon-NTH/HorizonGUI) for all the graphics-related functionality of the application.

## License

ShapeDrawer is licensed under the [MIT license](https://github.com/Horizon-NTH/ShapeDrawer/blob/master/LICENSE).