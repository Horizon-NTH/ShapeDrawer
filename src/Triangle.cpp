#include "../include/ShapeDrawer/Triangle.h"

Triangle::Triangle(cv::Point firstVertex, cv::Point secondVertex, cv::Point thirdVertex, cv::Scalar color, int thickness) :
	Shape(TRIANGLE, color, thickness, std::array<cv::Point, 3>{firstVertex, secondVertex, thirdVertex})
{
}

void Triangle::draw(const std::shared_ptr<cv::Mat>& image) const
{
	const auto& data = std::get<2>(m_data);
	if (m_thickness != -1)
	{
		cv::polylines(*image, data, true, m_color, m_thickness);
	}
	else
	{
		cv::fillPoly(*image, data, m_color);
	}
}

