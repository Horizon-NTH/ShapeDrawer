#pragma once

#include "Include.h"
#include "InputManager.h"

class ShapeDrawer
{
public:
	ShapeDrawer();

	void start();

private:
	std::shared_ptr<hgui::kernel::Window> m_window;
	std::shared_ptr<hgui::kernel::Monitor> m_monitor;
	std::shared_ptr<hgui::kernel::Font> m_font;

	std::vector<std::shared_ptr<hgui::kernel::Label>> m_texts;
	std::shared_ptr<hgui::kernel::Sprite> m_logo;
	std::shared_ptr<hgui::kernel::Canvas> m_canvas;

	void set_main_menu();
	void draw();
	void option_menu();
};
