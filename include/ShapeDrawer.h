#pragma once

#include "Include.h"
#include "DataManager.h"

class ShapeDrawer
{
public:
	ShapeDrawer();

	void start() const;

	[[nodiscard]] const std::shared_ptr<DataManager>& get_dataManager() const;

private:
	std::shared_ptr<hgui::kernel::Window> m_window;
	std::shared_ptr<hgui::kernel::Monitor> m_monitor;
	std::shared_ptr<hgui::kernel::Font> m_font;
	std::shared_ptr<DataManager> m_dataManager;

	std::vector<std::shared_ptr<hgui::kernel::Label>> m_texts;
	std::vector<std::shared_ptr<hgui::kernel::Button>> m_buttons;
	std::shared_ptr<hgui::kernel::Sprite> m_logo;
	std::shared_ptr<hgui::kernel::Canvas> m_canvas;

	ShapeToDraw m_toDraw;
	bool m_randomDrawing;
	std::vector<hgui::point> m_shapeDrawn;
	hgui::point m_cursorPosition;

	void set_main_menu();
	void set_option_menu();
	void set_input();
	void draw();
	void option_menu();
	void draw_shape();
	void draw_background() const;
};
