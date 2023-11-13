# ShapeDrawer

![ShapeDrawer's Logo](assets/ShapeDrawerName.png)

## Introduction

**ShapeDrawer** is a primitive shapes rendering application.  
With just a few clicks or simple commands, you can create basic shapes such as circles, rectangles, triangles, and lines. Additionally, you can easily import shape files and save them to enhance the creation of your shapes.

## Installation Instructions

You can get the code from scratch or download the [release version]().

* Get the source code

    First, clone the [repository](https://github.com/Horizon-NTH/ShapeDrawer) using [git](https://git-scm.com):

    ```bash
    git clone https://github.com/Horizon-NTH/ShapeDrawer
    ```

* Create the build environment

    The project uses [CMake](https://cmake.org/) to generate the build environment. Make sure you have CMake installed on your system.

    ```bash
    cd ShapeDrawer
    mkdir build && cd build
    cmake ..
    ```

* Build

  * **Using CMake**

    You can build directly using CMake:

    ```bash
    cmake --build .
    ```

    This command will create the executable `ShapeDrawer.exe` in the main folder of the git repository.

  * **Using Microsoft Visual Studio**

    Alternatively, you can use [Microsoft Visual Studio](https://visualstudio.microsoft.com/) to open the project and build it. Simply open the `ShapeDrawer.sln` file with Microsoft Visual Studio.

    ⚠️ Note: The application needs to be built with at least C++17.

## Usage

To learn how to use this application, please refer to the [documentation](docs/DOCUMENTATION.md).

## Dependencies

* **HorizonGUI**

    The code relies on [HorizonGUI](https://github.com/Horizon-NTH/HorizonGUI) for all the graphics-related functionality of the application.