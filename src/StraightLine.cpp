#include "../include/ShapeDrawer/StraightLine.h"

StraightLine::StraightLine(cv::Point firstVertex, cv::Point secondVertex, cv::Scalar color, int thickness) :
	Shape(LINE, color, thickness, std::make_tuple(firstVertex, secondVertex, thickness / 2))
{
}

void StraightLine::draw(const std::shared_ptr<cv::Mat>& image) const
{
	const auto& data = std::get<3>(m_data);
	cv::line(*image, std::get<0>(data), std::get<1>(data), m_color, m_thickness);
}
