#include "../include/DrawerManager.h"
/*
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
*/
