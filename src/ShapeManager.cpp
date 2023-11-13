#include "../include/ShapeDrawer/ShapeManager.h"

ShapeManager::ShapeManager()
{
}

void ShapeManager::draw(const std::shared_ptr<cv::Mat>& image) const
{
	for (const auto& shape : m_shapes)
	{
		shape->draw(image);
	}
}

void ShapeManager::create_rectangle(cv::Point topLeftVertex, cv::Point bottomRightVertex, cv::Scalar color, int thickness)
{
	m_shapes.push_back(std::make_unique<Rectangle>(topLeftVertex, bottomRightVertex, color, thickness));
}

void ShapeManager::create_triangle(cv::Point firstVertex, cv::Point secondVertex, cv::Point thirdVertex, cv::Scalar color, int thickness)
{
	m_shapes.push_back(std::make_unique<Triangle>(firstVertex, secondVertex, thirdVertex, color, thickness));
}

void ShapeManager::create_circle(cv::Point centerVertex, int radius, cv::Scalar color, int thickness)
{
	m_shapes.push_back(std::make_unique<Circle>(centerVertex, radius, color, thickness));
}

void ShapeManager::create_straight_line(cv::Point firstVertex, cv::Point secondVertex, cv::Scalar color, int thickness)
{
	m_shapes.push_back(std::make_unique<StraightLine>(firstVertex, secondVertex, color, thickness));
}

std::vector<std::unique_ptr<Shape>>& ShapeManager::get_shapes()
{
	return m_shapes;
}
