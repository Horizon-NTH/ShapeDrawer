#include "../include/ShapeDrawer/Rectangle.h"

Rectangle::Rectangle(cv::Point topLeftVertex, cv::Point rightBottmVertex, cv::Scalar color, int thickness) :
	Shape(RECTANGLE, color, thickness, std::make_pair(topLeftVertex, rightBottmVertex))
{
}

void Rectangle::draw(const std::shared_ptr<cv::Mat>& image) const
{
	const auto& data = std::get<0>(m_data);
	cv::rectangle(*image, data.first, data.second, m_color, m_thickness);
}
