#pragma once

#include "Include.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "StraightLine.h"

/*! @brief Class for managing shapes and drawing them on an image.
 *
 *  This class manages different shapes and provides methods to create and draw them on an image.
 *  It supports creating rectangles, triangles, circles, and straight lines.
 */
class ShapeManager
{
public:
    /*! @brief Constructor for the ShapeManager class. */
    ShapeManager();

    /*! @brief Draw all the shapes on the provided image.
     *
     *  @param image A shared pointer to the image on which shapes should be drawn.
     */
    void draw(const std::shared_ptr<cv::Mat>& image) const;

    /*! @brief Create a rectangle shape.
     *
     *  @param topLeftVertex The top-left vertex of the rectangle.
     *  @param bottomRightVertex The bottom-right vertex of the rectangle.
     *  @param color The color of the rectangle.
     *  @param thickness The thickness of the rectangle's outline.
     */
    void create_rectangle(cv::Point topLeftVertex, cv::Point bottomRightVertex, cv::Scalar color, int thickness);

    /*! @brief Create a triangle shape.
     *
     *  @param topVertex The top vertex of the triangle.
     *  @param bottomLeftVertex The bottom-left vertex of the triangle.
     *  @param bottomRightVertex The bottom-right vertex of the triangle.
     *  @param color The color of the triangle.
     *  @param thickness The thickness of the triangle's outline.
     */
    void create_triangle(cv::Point topVertex, cv::Point bottomLeftVertex, cv::Point bottomRightVertex, cv::Scalar color, int thickness);

    /*! @brief Create a circle shape.
     *
     *  @param centerVertex The center vertex of the circle.
     *  @param radius The radius of the circle.
     *  @param color The color of the circle.
     *  @param thickness The thickness of the circle's outline.
     */
    void create_circle(cv::Point centerVertex, int radius, cv::Scalar color, int thickness);

    /*! @brief Create a straight line shape.
     *
     *  @param firstVertex The first vertex of the line.
     *  @param secondVertex The second vertex of the line.
     *  @param color The color of the line.
     *  @param thickness The thickness of the line.
     */
    void create_straight_line(cv::Point firstVertex, cv::Point secondVertex, cv::Scalar color, int thickness);

    /*! @brief Get the vector of shapes.
     *
     *  @return A reference to the vector of shapes.
     */
    std::vector<std::unique_ptr<Shape>>& get_shapes();

private:
    std::vector<std::unique_ptr<Shape>> m_shapes;   //!< The vector of shapes managed by the ShapeManager.
};
