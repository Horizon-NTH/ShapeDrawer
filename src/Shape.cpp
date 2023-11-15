#include "../include/ShapeDrawer/Shape.h"

Shape::Shape(ShapeType type, cv::Scalar color, int thickness, ShapeData data) :
	m_type(type), m_color(color), m_thickness(thickness), m_data(data)
{
}

ShapeData Shape::get_data() const
{
	return m_data;
}

ShapeType Shape::get_type() const
{
	return m_type;
}

cv::Scalar Shape::get_color() const
{
	return m_color;
}

int Shape::get_thickness() const
{
	return m_thickness;
}
