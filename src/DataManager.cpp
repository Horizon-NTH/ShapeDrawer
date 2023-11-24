#include "../include/DataManager.h"

DataManager::DataManager(const std::shared_ptr<hgui::kernel::Drawer>& shapes) : m_shapes(shapes)
{
	m_names["circle"] = shape::CIRCLE;
	m_names["cercle"] = shape::CIRCLE;
	m_names["rectangle"] = shape::RECTANGLE;
	m_names["line"] = shape::LINE;
	m_names["ligne"] = shape::LINE;
	m_names["triangle"] = shape::TRIANGLE;
}

void DataManager::load(const std::string& path)
{
	if (std::ifstream file(path); file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			ss >> std::boolalpha;
			std::string name;

			ss >> name;
			std::ranges::transform(name, name.begin(), [](const unsigned char c) { return std::tolower(c); });

			if (!m_names.contains(name))
			{
				continue;
			}

			hgui::color color;
			float thickness;
			switch (m_names[name])
			{
			case shape::CIRCLE:
				{
					hgui::point center;
					float radius;
					bool fill;

					ss >> center.x;
					ss >> center.y;
					ss >> radius;
					ss >> color.r;
					ss >> color.g;
					ss >> color.b;
					ss >> fill;
					ss >> thickness;

					m_shapes->draw_circle(center, radius, color, fill, thickness);

					break;
				}
			case shape::RECTANGLE:
				{
					hgui::point topLeftVertex, bottomRightVertex;
					bool fill;

					ss >> topLeftVertex.x;
					ss >> topLeftVertex.y;
					ss >> bottomRightVertex.x;
					ss >> bottomRightVertex.y;
					ss >> color.r;
					ss >> color.g;
					ss >> color.b;
					ss >> fill;
					ss >> thickness;

					m_shapes->draw_rectangle(topLeftVertex, bottomRightVertex, color, fill, thickness);

					break;
				}
			case shape::LINE:
				{
					hgui::point firstVertex, secondVertex;

					ss >> firstVertex.x;
					ss >> firstVertex.y;
					ss >> secondVertex.x;
					ss >> secondVertex.y;
					ss >> color.r;
					ss >> color.g;
					ss >> color.b;
					ss >> thickness;

					m_shapes->draw_line(firstVertex, secondVertex, color, thickness);

					break;
				}
			case shape::TRIANGLE:
				{
					hgui::point firstVertex, secondVertex, thirdVertex;
					bool fill;

					ss >> firstVertex.x;
					ss >> firstVertex.y;
					ss >> secondVertex.x;
					ss >> secondVertex.y;
					ss >> thirdVertex.x;
					ss >> thirdVertex.y;
					ss >> color.r;
					ss >> color.g;
					ss >> color.b;
					ss >> fill;
					ss >> thickness;

					m_shapes->draw_triangle(firstVertex, secondVertex, thirdVertex, color, fill, thickness);

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

void DataManager::save(const std::string& path) const
{
	if (std::ofstream file(path); file.is_open())
	{
		for (const auto& shape : *m_shapes->get_shapes())
		{
			hgui::kernel::shape::ShapeData data = shape->get_data();
			if (const auto& points = std::get_if<std::pair<hgui::point, hgui::point>>(&data))
			{
				file << "rectangle " << points->first.x << " " << points->first.y << " "
						<< points->second.x << " " << points->second.y << " "
						<< shape->get_color().r << " " << shape->get_color().g << " " << shape->get_color().b << " "
						<< shape->get_thickness() << std::endl;
			}
			else if (const auto& points = std::get_if<std::pair<hgui::point, HGUI_PRECISION>>(&data))
			{
				file << "circle " << points->first.x << " " << points->first.y << " "
						<< points->second << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
			}
			else if (const auto& points = std::get_if<std::array<hgui::point, 3>>(&data))
			{
				file << "triangle " << points->at(0).x << " " << points->at(0).y << " "
						<< points->at(1).x << " " << points->at(1).y << " "
						<< points->at(2).x << " " << points->at(2).y << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
			}
			else if (const auto& points = std::get_if<std::tuple<hgui::point, hgui::point, HGUI_PRECISION>>(&data))
			{
				file << "line " << std::get<0>(*points).x << " " << std::get<0>(*points).y << " "
						<< std::get<1>(*points).x << " " << std::get<1>(*points).y << " "
						<< shape->get_color()[2] << " " << shape->get_color()[1] << " " << shape->get_color()[0] << " "
						<< shape->get_thickness() << std::endl;
			}
		}
		file.close();
	}
	else
	{
		throw std::runtime_error(("FAILED TO LOAD FILE : " + path).c_str());
	}
}
