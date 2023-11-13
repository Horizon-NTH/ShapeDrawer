#include "../include/ShapeDrawer/DataManager.h"

DataManager::DataManager(std::shared_ptr<ShapeManager> shapes)
	: m_shapes(shapes), m_names()
{
	m_names["circle"] = CIRCLE;
	m_names["cercle"] = CIRCLE;
	m_names["rectangle"] = RECTANGLE;
	m_names["line"] = LINE;
	m_names["ligne"] = LINE;
	m_names["triangle"] = TRIANGLE;
}

void DataManager::load(std::string path)
{
	std::string line;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			if (!parseur(line))
			{
				continue;
			}
			std::stringstream ss(line);
			std::string name;

			ss >> name;
			std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });

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

				m_shapes->create_circle(cv::Point(x, y), radius, cv::Scalar(b, g, r), thickness);

				break;
			case RECTANGLE:
			{
				int x1; int y1; int x2; int y2;

				ss >> x1; ss >> y1;
				ss >> x2; ss >> y2;
				ss >> r; ss >> g; ss >> b;
				ss >> thickness;

				m_shapes->create_rectangle(cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(b, g, r), thickness);

				break;
			}
			case LINE:
			{
				int x1; int y1; int x2; int y2;

				ss >> x1; ss >> y1;
				ss >> x2; ss >> y2;
				ss >> r; ss >> g; ss >> b;
				ss >> thickness;

				m_shapes->create_straight_line(cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(b, g, r), thickness);

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

				m_shapes->create_triangle(cv::Point(x1, y1), cv::Point(x2, y2), cv::Point(x3, y3), cv::Scalar(b, g, r), thickness);

				break;
			}
			default:
				break;
			}
		}
		myfile.close();
	}
	else
	{
		throw std::runtime_error(("FAILED TO LOAD FILE : " + path).c_str());
	}
}

void DataManager::save(std::string path)
{
	std::ofstream file(path);

	if (file.is_open())
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

bool DataManager::parseur(const std::string& line) const
{
	std::stringstream sstream(line);
	std::string name;
	sstream >> name;
	std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
	if (m_names.find(name) == m_names.end())
	{
		return false;
	}
	return true;
}
