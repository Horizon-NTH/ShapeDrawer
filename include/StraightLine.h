#pragma once

#include "Include.h"
#include "Shape.h"

/*! @brief Class representing a straight line shape.
 *
 *  This class inherits from the Shape base class and provides functionality specific to straight lines.
 */
class StraightLine : public Shape
{
public:
    /*! @brief Constructor for the StraightLine class.
     *
     *  @param firstVertex The first vertex of the straight line.
     *  @param secondVertex The second vertex of the straight line.
     *  @param color The color of the straight line.
     *  @param thickness The thickness of the straight line.
     */
    StraightLine(cv::Point firstVertex, cv::Point secondVertex, cv::Scalar color, int thickness);

    /*! @brief Draw the straight line on the image.
     *
     *  @param image A shared pointer to the image on which to draw the straight line.
     */
    void draw(const std::shared_ptr<cv::Mat>& image) const override;
};
