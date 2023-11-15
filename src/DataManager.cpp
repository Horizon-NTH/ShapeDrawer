#include "../include/DataManager.h"

DataManager::DataManager(const std::shared_ptr<hgui::kernel::Drawer>& shapes)
	: m_shapes(shapes), m_names()
{
	m_names["circle"] = CIRCLE;
	m_names["cercle"] = CIRCLE;
	m_names["rectangle"] = RECTANGLE;
	m_names["line"] = LINE;
	m_names["ligne"] = LINE;
	m_names["triangle"] = TRIANGLE;
}

void DataManager::load(const std::string& path)
{
	if (std::ifstream file(path); file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string name;

			ss >> name;
			std::ranges::transform(name, name.begin(), [](const unsigned char c) { return std::tolower(c); });

			if (!m_names.contains(name))
			{
				continue;
			}

			int r; int g; int b;
			int thickness;
			switch (m_names[name])
			{
			case CIRCLE:
				int x; int y; int radius;

				ss >> x; ss >> y;
				ss >> radius;
				ss >> r; ss >> g; ss >> b;
				ss >> thickness;

				m_shapes->draw_circle(hgui::point(x, y), radius, hgui::color(r, g, b), thickness == -1, thickness);

				break;
			case RECTANGLE:
			{
				int x1; int y1; int x2; int y2;

				ss >> x1; ss >> y1;
				ss >> x2; ss >> y2;
				ss >> r; ss >> g; ss >> b;
				ss >> thickness;

				m_shapes->draw_rectangle(hgui::point(x1, y1), hgui::point(x2, y2), hgui::color(r, g, b), thickness == -1, thickness);

				break;
			}
			case LINE:
			{
				int x1; int y1; int x2; int y2;

				ss >> x1; ss >> y1;
				ss >> x2; ss >> y2;
				ss >> r; ss >> g; ss >> b;
				ss >> thickness;

				m_shapes->draw_line(hgui::point(x1, y1), hgui::point(x2, y2), hgui::color(r, g, b), thickness);

				break;
			}
			case TRIANGLE:
			{
				int x1; int y1; int x2; int y2; int x3; int y3;

				ss >> x1; ss >> y1;
				ss >> x2; ss >> y2;
				ss >> x3; ss >> y3;
				ss >> r; ss >> g; ss >> b;
				ss >> thickness;

				m_shapes->draw_triangle(hgui::point(x1, y1), hgui::point(x2, y2), hgui::point(x3, y3), hgui::color(r, g, b), thickness == -1, thickness);

				break;
			}
			}
		}
		file.close();
	}
	else
	{
		throw std::runtime_error(("FAILED TO LOAD FILE : " + path).c_str());
	}
}

void DataManager::save(const std::string& path)
{
	if (std::ofstream file(path); file.is_open())
	{
		for (const auto& shape : m_shapes->get_shapes())
		{
			auto data = shape->get_data();
			switch (shape->get_type())
			{
			case RECTANGLE:
				if (const auto& points = std::get_if<std::pair<cv::Point, cv::Point>>(&data))
				{
					file << "rectangle " << points->first.x << " " << points->first.y << " "
						<< points->second.x << " " << points->second.y << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
				}
				break;
			case CIRCLE:
				if (const auto& points = std::get_if<std::pair<cv::Point, int>>(&data))
				{
					file << "circle " << points->first.x << " " << points->first.y << " "
						<< points->second << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
				}
				break;
			case TRIANGLE:
				if (const auto& points = std::get_if<std::array<cv::Point, 3>>(&data))
				{
					file << "triangle " << points->at(0).x << " " << points->at(0).y << " "
						<< points->at(1).x << " " << points->at(1).y << " "
						<< points->at(2).x << " " << points->at(2).y << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
				}
				break;
			case LINE:
				if (const auto& points = std::get_if<std::tuple<cv::Point, cv::Point, int>>(&data))
				{
					file << "line " << std::get<0>(*points).x << " " << std::get<0>(*points).y << " "
						<< std::get<1>(*points).x << " " << std::get<1>(*points).y << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
				}
				break;
			default:
				break;
			}
		}
		file.close();
	}
	else
	{
		throw std::runtime_error(("FAILED TO LOAD FILE : " + path).c_str());
	}
}