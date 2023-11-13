#pragma once

#include "Include.h"

/*! @brief Enumeration defining different types of shapes.
 *
 *  This enumeration represents the possible types of shapes,
 *  such as rectangle, triangle, circle, and line.
 */
enum ShapeType
{
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    LINE
};

/*! @brief Alias for the ShapeData variant type.
 *
 *  This alias represents the ShapeData variant type, which can
 *  hold different types of data depending on the shape type.
 */
typedef std::variant<
    std::pair<cv::Point, cv::Point>,    // For rectangle and line
    std::pair<cv::Point, int>,          // For circle
    std::array<cv::Point, 3>,           // For triangle
    std::tuple<cv::Point, cv::Point, int>  // For line
> ShapeData;

ShapeData operator-(const ShapeData& data, int value);
ShapeData operator+(const ShapeData& data, int value);

/*! @brief Base class for different shapes.
 *
 *  This class serves as the base class for different shape types.
 *  It provides common properties and methods for shapes, such as
 *  color, thickness, and drawing functionality.
 */
class Shape
{
public:
    /*! @brief Constructor for the Shape class.
     *
     *  @param type      The type of the shape.
     *  @param color     The color of the shape.
     *  @param thickness The thickness of the shape's outline.
     *  @param data      The shape data specific to the shape type.
     */
    Shape(ShapeType type, cv::Scalar color, int thickness, ShapeData data);

    /*! @brief Pure virtual method to draw the shape on an image.
     *
     *  This method must be overridden by the derived classes.
     *  It draws the shape on the provided image using the specified parameters.
     *
     *  @param image    The image on which to draw the shape.
     */
    virtual void draw(const std::shared_ptr<cv::Mat>& image) const = 0;

    /*! @brief Getter method to retrieve the shape data.
     *
     *  @return The shape data.
     */
    ShapeData get_data() const;

    /*! @brief Getter method to retrieve the shape type.
     *
     *  @return The shape type.
     */
    ShapeType get_type() const;

    /*! @brief Getter method to retrieve the shape color.
     *
     *  @return The shape color.
     */
    cv::Scalar get_color() const;

    /*! @brief Getter method to retrieve the shape thickness.
     *
     *  @return The shape thickness.
     */
    int get_thickness() const;

protected:
    ShapeType m_type;       //!< Type of the shape
    cv::Scalar m_color;     //!< Color of the shape
    int m_thickness;        //!< Thickness of the shape's outline
    ShapeData m_data;       //!< Data specific to the shape type
};