#include "../include/ShapeDrawer/Circle.h"

Circle::Circle(cv::Point center, int radius, cv::Scalar color, int thickness) :
	Shape(CIRCLE, color,thickness, std::make_pair(center, radius))
{
}

void Circle::draw(const std::shared_ptr<cv::Mat>& image) const
{
	const auto& data = std::get<1>(m_data);
	cv::circle(*image, data.first, data.second, m_color, m_thickness);
}
