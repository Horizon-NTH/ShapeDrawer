#pragma once

#include "Include.h"
#include "Shape.h"

/*! @brief Class representing a rectangle shape.
 *
 *  This class inherits from the Shape base class and provides functionality specific to rectangles.
 */
class Rectangle : public Shape
{
public:
    /*! @brief Constructor for the Rectangle class.
     *
     *  @param topLeftVertex The top-left vertex of the rectangle.
     *  @param rightBottmVertex The bottom-right vertex of the rectangle.
     *  @param color The color of the rectangle.
     *  @param thickness The thickness of the rectangle's outline.
     */
    Rectangle(cv::Point topLeftVertex, cv::Point rightBottmVertex, cv::Scalar color, int thickness);

    /*! @brief Draw the rectangle on the image.
     *
     *  @param image A shared pointer to the image on which to draw the rectangle.
     */
    void draw(const std::shared_ptr<cv::Mat>& image) const override;
};
