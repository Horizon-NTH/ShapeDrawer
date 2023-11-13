# ShapeDrawer - Documentation

## Start

To start the application, you just need to create a `ShapeDrawer` object and call its `run` method:

```cpp
ShapeDrawer application;
application.run();
```

By calling the `run` method, a fullscreen window will be created.

⚠️ The `run` method is an infinite loop, so make sure to place all your instructions before calling it.

## End

To close the application, you just need to press the [ESCAPE] key on your keyboard.

## Drawing

There are multiple ways to draw a shape with this application. Here is a list of all the ways to draw shapes:

* **Command Line**

  You can draw a shape using the `ShapeManager` object of your application, which you can obtain with the following command:

  ```cpp
  auto shapeManager = application.get_shapeManager();
  ```

  The `shapeManager` is an `std::shared_ptr`.

  You can use this manager to create different shapes:

  * **Circle**

    ```cpp
    shapeManager->create_circle(cv::Point centerVertex, int radius, cv::Scalar color, int thickness);
    ```

    Parameters:

    * `centerVertex`: Circle's center.
    * `radius`: Circle's radius.
    * `color`: Circle's color.
    * `thickness`: Circle's thickness. Use **-1** if you want to fill the circle.

  * **Rectangle**

    ```cpp
    shapeManager->create_rectangle(cv::Point topLeftVertex, cv::Point bottomRightVertex, cv::Scalar color, int thickness);
    ```

    Parameters:

    * `topLeftVertex`: Rectangle's top left vertex.
    * `bottomRightVertex`: Rectangle's bottom right vertex.
    * `color`: Rectangle's color.
    * `thickness`: Rectangle's thickness. Use **-1** if you want to fill the rectangle.

  * **Triangle**

    ```cpp
    shapeManager->create_triangle(cv::Point firstVertex, cv::Point secondVertex, cv::Point thirdVertex, cv::Scalar color, int thickness);
    ```

    Parameters:

    * `firstVertex`: Triangle's first vertex.
    * `secondVertex`: Triangle's second vertex.
    * `thirdVertex`: Triangle's third vertex.
    * `color`: Triangle's color.
    * `thickness`: Triangle's thickness. Use **-1** if you want to fill the triangle.

  * **Line**

    ```cpp
    shapeManager->create_straight_line(cv::Point firstVertex, cv::Point secondVertex, cv::Scalar color, int thickness);
    ```

    Parameters:

    * `firstVertex`: Line's first extremity.
    * `secondVertex`: Line's second extremity.
    * `color`: Line's color.
    * `thickness`: Line's thickness. Use **-1** if you want to fill the line.

  ⚠️ Remember to place these lines before the render loop in the `run` method.

* **File**

  You can import and save data to a file.

  To load data from a file, you need to use the `DataManager` object of your application, which you can obtain with the following command:

  ```cpp
  auto dataManager = application.get_dataManager();
  ```

  The `dataManager` is an `std::shared_ptr`.

  To load data from a file, use the following command:

  ```cpp
  shapeManager->load(std::string path);
  ```

  Parameters:

  * `path`: File's path.

  This will add all the shapes from the file to the `ShapeManager`.

  To save data to a file

, use the following command:

  ```cpp
  shapeManager->save(std::string path);
  ```

  Parameters:

  * `path`: File's path.

  This will store all the shapes that are in the `ShapeManager` inside the file.

  You can use the `DataManager` to load and save data. Here is the data structure used:

  * **Circle**

    ```
    CIRCLE x y radius r g b thickness
    ```

    Parameters:

    * `CIRCLE`: String "CIRCLE".
    * `x`: x-coordinate of the circle's center.
    * `y`: y-coordinate of the circle's center.
    * `radius`: Circle's radius.
    * `r`: Red component of the circle's color.
    * `g`: Green component of the circle's color.
    * `b`: Blue component of the circle's color.
    * `thickness`: Circle's thickness.

  * **Rectangle**

    ```
    RECTANGLE x1 y1 x2 y2 r g b thickness
    ```

    Parameters:

    * `RECTANGLE`: String "RECTANGLE".
    * `x1`: x-coordinate of the rectangle's top left vertex.
    * `y1`: y-coordinate of the rectangle's top left vertex.
    * `x2`: x-coordinate of the rectangle's bottom right vertex.
    * `y2`: y-coordinate of the rectangle's bottom right vertex.
    * `r`: Red component of the rectangle's color.
    * `g`: Green component of the rectangle's color.
    * `b`: Blue component of the rectangle's color.
    * `thickness`: Rectangle's thickness.

  * **Triangle**

    ```
    TRIANGLE x1 y1 x2 y2 x3 y3 r g b thickness
    ```

    Parameters:

    * `TRIANGLE`: String "TRIANGLE".
    * `x1`: x-coordinate of the triangle's first vertex.
    * `y1`: y-coordinate of the triangle's first vertex.
    * `x2`: x-coordinate of the triangle's second vertex.
    * `y2`: y-coordinate of the triangle's second vertex.
    * `x3`: x-coordinate of the triangle's third vertex.
    * `y3`: y-coordinate of the triangle's third vertex.
    * `r`: Red component of the triangle's color.
    * `g`: Green component of the triangle's color.
    * `b`: Blue component of the triangle's color.
    * `thickness`: Triangle's thickness.

  * **Line**

    ```
    LINE x1 y1 x2 y2 r g b thickness
    ```

    Parameters:

    * `LINE`: String "LINE".
    * `x1`: x-coordinate of the line's first vertex.
    * `y1`: y-coordinate of the line's first vertex.
    * `x2`: x-coordinate of the line's second vertex.
    * `y2`: y-coordinate of the line's second vertex.
    * `r`: Red component of the line's color.
    * `g`: Green component of the line's color.
    * `b`: Blue component of the line's color.
    * `thickness`: Line's thickness.

* **Input**

  When the application is running, you can also draw and delete shapes using your mouse and keyboard. With the keyboard, you can choose the shape, color, and thickness to use when drawing with your mouse clicks.

  Here is a detailed list of keyboard actions:

  * `DELETE`: Delete all the shapes.
  * `BACKSPACE`: Delete the last drawn shape.
  * `ENTER`: Change the drawing mode.
  * `+`: Increase the drawing shape's thickness.
  * `-`: Decrease the drawing shape's thickness.
  * `C`: Set the drawing shape to a circle.
  * `R`: Set the drawing shape to a rectangle.
  * `T`: Set the drawing shape to a triangle.
  * `L`: Set the drawing shape to a line.
  * `N`: Change the drawing color to a new random color.
  * `F`: Toggle between filled or unfilled drawing shape.

  Here is a detailed list of mouse actions:

  * `LEFT-CLICK`: Draw a shape based on the drawing settings.
  * `RIGHT-CLICK`: Delete the shape at the clicked position.
  * `SCROLL-UP`: Increase the drawing shape's thickness.
  * `SCROLL-DOWN`: Decrease the drawing shape's thickness.

  Additionally, there are two drawing modes:

  * **Random drawing**: It creates a shape with a random size around your click.
  * **Classic drawing**: You place one vertex at a time to construct the shape.