#include "../include/ShapeDrawer/ShapeDrawer.h"
#include <cstddef>

ShapeDrawer::ShapeDrawer() :
	m_window(std::nullptr_t),
	m_shapes(std::make_shared<ShapeManager>()), m_shouldClose(false),
	m_data(nullptr)
{
	m_data = std::make_shared<DataManager>(m_shapes);
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	main_menu();
	InputManager::init(this);
}

void ShapeDrawer::run() const
{
	while (!m_shouldClose)
	{
		auto image = m_window->new_image();
		InputManager::key_callback();
		m_shapes->draw(image);
		InputManager::draw();
		cv::imshow(m_window->get_name(), *image);
	}
}

const std::shared_ptr<Window>& ShapeDrawer::get_window() const
{
	return m_window;
}
const std::shared_ptr<ShapeManager>& ShapeDrawer::get_shapeManager() const
{
	return m_shapes;
}

const std::shared_ptr<DataManager>& ShapeDrawer::get_dataManager() const
{
	return m_data;
}

void ShapeDrawer::close()
{
	m_shouldClose = true;
}

void ShapeDrawer::main_menu() const
{
	auto logo = cv::imread("../assets/ShapeDrawerName.png");
	if (logo.empty())
	{
		throw std::runtime_error("FAILED TO LOAD IMAGE");
	}
	cv::imshow(m_window->get_name(), logo);
	cv::waitKey(0);
}
