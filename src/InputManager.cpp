#include "../include/ShapeDrawer/InputManager.h"

bool isPointIn(ShapeType type, ShapeData data, cv::Point point)
{
	switch (type)
	{
	case RECTANGLE:
		if (auto points = std::get_if<std::pair<cv::Point, cv::Point>>(&data))
		{
			return points->first.x <= point.x && points->first.y <= point.y &&
				points->second.x >= point.x && points->second.y >= point.y;
		}
		break;
	case TRIANGLE:
		if (auto points = std::get_if<std::array<cv::Point, 3>>(&data))
		{
			auto area = [](const cv::Point& v1, const cv::Point& v2, const cv::Point v3) -> double
			{
				return std::abs((v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0);
			};
			cv::Point v1 = points->at(0), v2 = points->at(1), v3 = points->at(2);
			return area(point, v1, v2) + area(point, v2, v3) + area(point, v3, v1) - area(v1, v2, v3) < 1e-6;
		}
		break;
	case CIRCLE:
		if (auto points = std::get_if<std::pair<cv::Point, int>>(&data))
		{
			return cv::norm(point - points->first) <= points->second;
		}
		break;
	case LINE:
		if (auto points = std::get_if<std::tuple<cv::Point, cv::Point, int>>(&data))
		{
			if (!(cv::norm(std::get<0>(*points)) < cv::norm(std::get<1>(*points))))
			{
				cv::Point temp = std::get<0>(*points);
				std::get<0>(*points) = std::get<1>(*points);
				std::get<1>(*points) = temp;
			}
			double a = std::get<1>(*points).y - std::get<0>(*points).y;
			double b = std::get<0>(*points).x - std::get<1>(*points).x;
			double c = std::get<1>(*points).x * std::get<0>(*points).y - std::get<0>(*points).x * std::get<1>(*points).y;
			double distance = std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
			bool isNearExtremity = cv::norm(std::get<0>(*points) - point) <= std::get<2>(*points) ||
				cv::norm(std::get<1>(*points) - point) <= std::get<2>(*points);
			bool isNearLine = (a > 0) ?
				(distance <= std::get<2>(*points)
					&& std::get<0>(*points).x <= point.x && std::get<0>(*points).y <= point.y
					&& std::get<1>(*points).x >= point.x && std::get<1>(*points).y >= point.y) :
				(distance <= std::get<2>(*points)
					&& std::get<0>(*points).x <= point.x && std::get<0>(*points).y >= point.y
					&& std::get<1>(*points).x >= point.x && std::get<1>(*points).y <= point.y);
			return  isNearExtremity || isNearLine;
		}
		break;
	default:
		break;
	}
}
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
		double k = (currentSize - 10.0 * value) / currentSize;
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

ShapeToDraw InputManager::m_toDraw;
ShapeDrawer* InputManager::m_app(nullptr);
bool InputManager::m_randomDrawing(false);
decltype(InputManager::m_shapeDrawn) InputManager::m_shapeDrawn;
cv::Point InputManager::m_cursorPosition;

void InputManager::init(ShapeDrawer* app)
{
	static bool alreadyInitialized = false;
	if (!alreadyInitialized)
	{
		alreadyInitialized = true;
		m_app = app;
		m_toDraw = { CIRCLE, cv::Scalar(255), 50 };
		cv::setMouseCallback(m_app->get_window()->get_name(), mouse_callback);
	}
	else
	{
		throw std::runtime_error("YOU ALREADY HAVE INITIALIZE THE CLASS");
	}
}

void InputManager::key_callback()
{
	int key = cv::waitKey(25);
	if (key == 27)
	{
		m_app->close();
	}
	else if (key == 0)
	{
		m_app->get_shapeManager()->get_shapes().clear();
	}
	else if (key == 8)
	{
		if (!m_app->get_shapeManager()->get_shapes().empty())
		{
			m_app->get_shapeManager()->get_shapes().pop_back();
		}
	}
	else if (key == 13)
	{
		if (m_randomDrawing)
		{
			m_randomDrawing = false;
		}
		else
		{
			m_randomDrawing = true;
			m_shapeDrawn.clear();
		}
	}
	else if (key == 99)
	{
		std::get<0>(m_toDraw) = CIRCLE;
	}
	else if (key == 114)
	{
		std::get<0>(m_toDraw) = RECTANGLE;
	}
	else if (key == 108)
	{
		std::get<0>(m_toDraw) = LINE;
	}
	else if (key == 116)
	{
		std::get<0>(m_toDraw) = TRIANGLE;
	}
	else if (key == 102)
	{
		static int lastThickness = -1;
		if (std::get<2>(m_toDraw) == -1)
		{
			std::get<2>(m_toDraw) = lastThickness;
		}
		else
		{
			lastThickness = std::get<2>(m_toDraw);
			std::get<2>(m_toDraw) = -1;
		}
	}
	else if (key == 110)
	{
		std::get<1>(m_toDraw) = cv::Scalar(std::rand() % 256, std::rand() % 256, std::rand() % 256);;
	}
	else if (key == 43)
	{
		std::get<2>(m_toDraw) = std::max(std::get<2>(m_toDraw) + 5, 1);
	}
	else if (key == 45)
	{
		std::get<2>(m_toDraw) = std::max(std::get<2>(m_toDraw) - 5, 1);
	}
}

void InputManager::mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	auto randomPoint = [](const cv::Size& windowSize) -> cv::Point
	{
		return cv::Point(std::rand() % windowSize.width, std::rand() % windowSize.height);
	};
	cv::Point click = cv::Point(x, y);

	if (event == cv::EVENT_LBUTTONDOWN)
	{
		if (m_randomDrawing)
		{
			switch (std::get<0>(m_toDraw))
			{
			case RECTANGLE:
			{
				cv::Point firstPoint, secondPoint;
				do
				{
					firstPoint = randomPoint(m_app->get_window()->get_size());
					secondPoint = randomPoint(m_app->get_window()->get_size());
				} while (!isPointIn(RECTANGLE, std::make_pair(firstPoint, secondPoint), click));
				m_app->get_shapeManager()->create_rectangle(firstPoint, secondPoint,
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
			}
			break;
			case CIRCLE:
				m_app->get_shapeManager()->create_circle(cv::Point(x, y),
					std::rand() % m_app->get_window()->get_size().height / 2.0f,
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				break;
			case TRIANGLE:
			{
				cv::Point firstPoint, secondPoint, thirdPoint;
				do
				{
					firstPoint = randomPoint(m_app->get_window()->get_size());
					secondPoint = randomPoint(m_app->get_window()->get_size());
					thirdPoint = randomPoint(m_app->get_window()->get_size());
				} while (!isPointIn(TRIANGLE,
					std::array<cv::Point, 3>{firstPoint, secondPoint, thirdPoint}, click));
				m_app->get_shapeManager()->create_triangle(firstPoint, secondPoint, thirdPoint,
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
			}
			break;
			case LINE:
			{
				cv::Point firstPoint, secondPoint;
				do
				{
					firstPoint = randomPoint(m_app->get_window()->get_size());
					secondPoint = randomPoint(m_app->get_window()->get_size());
				} while (!isPointIn(LINE, std::tuple(firstPoint, secondPoint, std::get<2>(m_toDraw) / 2), click));
				m_app->get_shapeManager()->create_straight_line(firstPoint, secondPoint,
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
			}
			break;
			default:
				break;
			}
		}
		else
		{
			m_shapeDrawn.push_back(click);
		}
	}
	else if (event == cv::EVENT_RBUTTONDOWN)
	{
		if (m_randomDrawing || !m_shapeDrawn.size())
		{
			auto& shapes = m_app->get_shapeManager()->get_shapes();
			auto shapeToDelete = std::find_if(shapes.rbegin(), shapes.rend(), [click](const std::unique_ptr<Shape>& shape) -> bool
				{
					if (shape->get_thickness() != -1 && shape->get_type() != LINE)
					{
						return isPointIn(shape->get_type(), shape->get_data() + shape->get_thickness() / 2, click) &&
							!isPointIn(shape->get_type(), shape->get_data() - shape->get_thickness() / 2, click);
					}
					else
					{
						return isPointIn(shape->get_type(), shape->get_data(), click);
					}
					switch (shape->get_type())
					{
					case RECTANGLE:
					{
						if (shape->get_thickness() != -1)
						{
							return isPointIn(shape->get_type(), shape->get_data() + shape->get_thickness() / 2, click) &&
								!isPointIn(shape->get_type(), shape->get_data() - shape->get_thickness() / 2, click);
						}
						return isPointIn(shape->get_type(), shape->get_data(), click);
					}
					break;
					case CIRCLE:
						if (shape->get_thickness() != -1)
						{
							return isPointIn(shape->get_type(), shape->get_data() + shape->get_thickness() / 2, click) &&
								!isPointIn(shape->get_type(), shape->get_data() - shape->get_thickness() / 2, click);
						}
						return isPointIn(shape->get_type(), shape->get_data(), click);
						break;
					case TRIANGLE:
					{
						auto data = shape->get_data();
						auto points = std::get_if<std::array<cv::Point, 3>>(&data);
						if (shape->get_thickness() != -1)
						{
							return isPointIn(LINE, std::make_tuple(points->at(0), points->at(1), shape->get_thickness() / 2), click)
								|| isPointIn(LINE, std::make_tuple(points->at(1), points->at(2), shape->get_thickness() / 2), click)
								|| isPointIn(LINE, std::make_tuple(points->at(2), points->at(0), shape->get_thickness() / 2), click);
						}
						return isPointIn(shape->get_type(), shape->get_data(), click);
					}
					break;
					case LINE:
					{
						return isPointIn(shape->get_type(), shape->get_data(), click);
					}
					break;
					default:
						break;
					}
				});
			if (shapeToDelete != shapes.rend())
			{
				shapes.erase(std::prev(shapeToDelete.base()));
			}
		}
		else
		{
			m_shapeDrawn.clear();
		}
	}
	else if (event == cv::EVENT_MOUSEWHEEL)
	{
		int delta = cv::getMouseWheelDelta(flags);
		std::get<2>(m_toDraw) = std::max(std::get<2>(m_toDraw) + delta / 30, 1);
	}
	else if (event == cv::EVENT_MOUSEMOVE)
	{
		m_cursorPosition = click;
	}
}

void InputManager::draw()
{
	if (!m_randomDrawing)
	{
		switch (std::get<0>(m_toDraw))
		{
		case LINE:
			if (m_shapeDrawn.size() == 2)
			{
				m_app->get_shapeManager()->create_straight_line(m_shapeDrawn.at(0), m_shapeDrawn.at(1),
					std::get<1>(m_toDraw), std::max(std::get<2>(m_toDraw), 1));
				m_shapeDrawn.clear();
			}
			else if (m_shapeDrawn.size() == 1)
			{
				cv::line(*m_app->get_window()->get_image(), m_shapeDrawn.at(0), m_cursorPosition, std::get<1>(m_toDraw), std::max(std::get<2>(m_toDraw), 1));
			}
			break;
		case CIRCLE:
			if (m_shapeDrawn.size() == 2)
			{
				m_app->get_shapeManager()->create_circle(m_shapeDrawn.at(0), cv::norm(m_shapeDrawn.at(0) - m_shapeDrawn.at(1)),
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			else if (m_shapeDrawn.size() == 1)
			{
				cv::circle(*m_app->get_window()->get_image(), m_shapeDrawn.at(0), cv::norm(m_shapeDrawn.at(0) - m_cursorPosition), std::get<1>(m_toDraw), std::get<2>(m_toDraw));
			}
			break;
		case RECTANGLE:
			if (m_shapeDrawn.size() == 2)
			{
				m_app->get_shapeManager()->create_rectangle(m_shapeDrawn.at(0), m_shapeDrawn.at(1),
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			else if (m_shapeDrawn.size() == 1)
			{
				cv::rectangle(*m_app->get_window()->get_image(), m_shapeDrawn.at(0), m_cursorPosition, std::get<1>(m_toDraw), std::get<2>(m_toDraw));
			}
			break;
		case TRIANGLE:
			if (m_shapeDrawn.size() == 1)
			{
				cv::line(*m_app->get_window()->get_image(), m_shapeDrawn.at(0), m_cursorPosition, std::get<1>(m_toDraw), std::max(std::get<2>(m_toDraw), 1));
			}
			else if (m_shapeDrawn.size() == 2)
			{
				auto points = m_shapeDrawn;
				points.push_back(m_cursorPosition);
				if (std::get<2>(m_toDraw) != -1)
				{
					cv::polylines(*m_app->get_window()->get_image(), points, true, std::get<1>(m_toDraw), std::max(std::get<2>(m_toDraw), 1));
				}
				else
				{
					cv::fillPoly(*m_app->get_window()->get_image(), points, std::get<1>(m_toDraw));
				}
			}
			else if (m_shapeDrawn.size() == 3)
			{
				m_app->get_shapeManager()->create_triangle(m_shapeDrawn.at(0), m_shapeDrawn.at(1), m_shapeDrawn.at(2),
					std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			break;
		default:
			break;
		}
	}
}
