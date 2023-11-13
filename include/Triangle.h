#pragma once

#include "Include.h"
#include "Shape.h"

/*! @brief Class representing a triangle shape.
 *
 *  This class represents a triangle shape that extends the base Shape class.
 *  It provides functionality to draw a triangle on an image using three vertices.
 */
class Triangle : public Shape
{
public:
    /*! @brief Constructor for the Triangle class.
     *
     *  @param firstVertex   The first vertex of the triangle.
     *  @param secondVertex  The second vertex of the triangle.
     *  @param thirdVertex   The third vertex of the triangle.
     *  @param color         The color of the triangle.
     *  @param thickness     The thickness of the triangle's outline.
     */
    Triangle(cv::Point firstVertex, cv::Point secondVertex, cv::Point thirdVertex, cv::Scalar color, int thickness);

    /*! @brief Method to draw the triangle on an image.
     *
     *  This method overrides the draw() method from the base Shape class.
     *  This method draws the triangle on the provided image using the specified parameters.
     *
     *  @param image    The image on which to draw the triangle.
     */
    void draw(const std::shared_ptr<cv::Mat>& image) const override;
};
