#pragma once

#include "Include.h"
#include "Shape.h"

/*! @brief Class representing a circle shape.
 *
 *  This class inherits from the Shape class and provides functionality to draw a circle on an image.
 */
class Circle : public Shape
{
public:
    /*! @brief Constructor for the Circle class.
     *
     *  @param center The center point of the circle.
     *  @param radius The radius of the circle.
     *  @param color The color of the circle.
     *  @param thickness The thickness of the circle's outline.
     */
    Circle(cv::Point center, int radius, cv::Scalar color, int thickness);

    /*! @brief Draw the circle on the image.
     *
     *  @param image A shared pointer to the image on which the circle is to be drawn.
     */
    void draw(const std::shared_ptr<cv::Mat>& image) const override;
};
