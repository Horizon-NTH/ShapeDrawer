#include "../include/ShapeDrawer/Shape.h"

ShapeData operator-(const ShapeData& data, int value)
{
	if (auto points = std::get_if<std::pair<cv::Point, cv::Point>>(&data))
	{
		return std::make_pair(points->first + cv::Point(value, value),
			points->second - cv::Point(value, value));
	}
	else if (auto points = std::get_if<std::pair<cv::Point, int>>(&data))
	{
		return std::make_pair(points->first, points->second - value);
	}
	else if (auto points = std::get_if<std::array<cv::Point, 3>>(&data))
	{
		cv::Point center = (points->at(0) + points->at(1) + points->at(2)) / 3;
		double currentSize = cv::norm(points->at(1) - points->at(0));
		double k = (currentSize - 10.0 * value)/currentSize;
		std::array<cv::Point, 3> newPoints;
		for (int i = 0; i < 3; ++i)
		{
			cv::Point displacement = points->at(i) - center;
			newPoints[i] = center + (displacement * k);
		}
		return newPoints;
	}
	else if (auto points = std::get_if<std::tuple<cv::Point, cv::Point, int>>(&data))
	{
		return std::make_tuple(std::get<0>(*points), std::get<1>(*points), std::max(std::get<2>(*points) - value, 0));
	}
	return data;
}

ShapeData operator+(const ShapeData& data, int value)
{
	if (auto points = std::get_if<std::pair<cv::Point, cv::Point>>(&data))
	{
		return std::make_pair(points->first - cv::Point(value, value),
			points->second + cv::Point(value, value));
	}
	else if (auto points = std::get_if<std::pair<cv::Point, int>>(&data))
	{
		return std::make_pair(points->first, points->second + value);
	}
	else if (auto points = std::get_if<std::array<cv::Point, 3>>(&data))
	{
		cv::Point center = (points->at(0) + points->at(1) + points->at(2)) / 3;
		double currentSize = cv::norm(points->at(1) - points->at(0));
		double k = (currentSize + 10.0 * value) / currentSize;
		std::array<cv::Point, 3> newPoints;
		for (int i = 0; i < 3; ++i)
		{
			cv::Point displacement = points->at(i) - center;
			newPoints[i] = center + (displacement * k);
		}
		return newPoints;
	}
	else if (auto points = std::get_if<std::tuple<cv::Point, cv::Point, int>>(&data))
	{
		return std::make_tuple(std::get<0>(*points), std::get<1>(*points), std::get<2>(*points) + value);
	}
	return data;
}

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
