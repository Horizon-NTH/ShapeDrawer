#include "../include/ShapeDrawer.h"

ShapeDrawer::ShapeDrawer() :
	m_window(nullptr), m_monitor(nullptr),
	m_font(nullptr), m_logo(nullptr),
	m_canvas(nullptr)
{
	//Library initialization//
	InputManager::init(this);
	hgui::init();
	//Winodw creation//
	m_monitor = hgui::MonitorManager::get_primary_monitor();
	m_window = hgui::WindowManager::create("ShapeDrawer", m_monitor->get_size(),
		hgui::point(0), hgui::image_loader("assets/texture/logo.png"), nullptr, { hgui::WindowOption(hgui::options::MAXIMIZED, true) });
	//Tag creation//
	hgui::TagManager::create_tag("main_menu");
	hgui::TagManager::create_tag("draw");
	hgui::TagManager::create_tag("option");
	//Load Font
	m_font = hgui::FontManager::create("assets/fonts/montserrat/Montserrat-Regular.otf");
	//Binding
	hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), hgui::end);
	//OptionMenu
	/*
	constexpr int BUTTON_SIZE = 100;
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{
			render(FractalsType::SAME);
		}, hgui::size(BUTTON_SIZE), hgui::point(5_em),
		hgui::TextureManager::create(hgui::image_loader("assets/textures/option.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{
			if (auto fractal = std::dynamic_pointer_cast<Mandelbrot>(m_fractal))
			{
				m_fractal = std::static_pointer_cast<Fractal>(std::make_shared<MandelbrotExtended>(fractal));
			}
		}, hgui::size(BUTTON_SIZE), hgui::point(5_em, 5_em + BUTTON_SIZE),
		hgui::TextureManager::create(hgui::image_loader("assets/textures/zoom.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{
			if (auto fractal = std::dynamic_pointer_cast<MandelbrotExtended>(m_fractal))
			{
				m_fractal = std::make_shared<Mandelbrot>(fractal);
			}
		}, hgui::size(BUTTON_SIZE), hgui::point(5_em + BUTTON_SIZE),
		hgui::TextureManager::create(hgui::image_loader("assets/textures/perf.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{
			if (m_fractal)
			{
				m_fractal->get_shader()->use().set_int("color", 0);
			}
		}, hgui::size(100), hgui::point(5_em, 5_em + 2 * BUTTON_SIZE),
		hgui::TextureManager::create(hgui::image_loader("assets/textures/wave.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{ 
			if (m_fractal)
			{
				m_fractal->get_shader()->use().set_int("color", 1);
			}
		}, hgui::size(100), hgui::point(5_em + BUTTON_SIZE, 5_em + 2 * BUTTON_SIZE),
		nullptr, hgui::color(1.0, 0.0), static_cast<float>(INT_MAX), "HSV", m_font, HGUI_COLOR_WHITE));
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{
			if (m_fractal)
			{
				m_fractal->get_shader()->use().set_int("color", 2);
			}
		}, hgui::size(100), hgui::point(5_em + 2 * BUTTON_SIZE, 5_em + 2 * BUTTON_SIZE),
		nullptr, hgui::color(1.0, 0.0), static_cast<float>(INT_MAX), "HSL", m_font, HGUI_COLOR_WHITE));
	m_buttons.push_back(hgui::ButtonManager::create([&]() 
		{
			if (m_fractal)
			{
				m_fractal->get_shader()->use().set_int("color", 3);
			}
		}, hgui::size(100), hgui::point(5_em + 3 * BUTTON_SIZE, 5_em + 2 * BUTTON_SIZE),
		nullptr, hgui::color(1.0, 0.0), static_cast<float>(INT_MAX), "LCH", m_font, HGUI_COLOR_WHITE));
		*/
	set_main_menu();
}

void ShapeDrawer::start()
{
	set_main_menu();

	hgui::Widget::active({ "main_menu" });
	hgui::Renderer::draw({ "main_menu" });
	hgui::Renderer::loop();
}

void ShapeDrawer::draw()
{
	hgui::TagManager::set_current_tag("draw");
	m_canvas = hgui::CanvasManager::create(nullptr, m_window->get_size(), hgui::point(0), HGUI_COLOR_BLACK);
	if (hgui::KeyBoardManager::is_bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE)))
	{
		hgui::KeyBoardManager::unbind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE));
	}
	hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), [&]() { option_menu(); });
	hgui::Widget::active({ "draw" });
	hgui::Renderer::draw({ "draw" });
	hgui::Renderer::draw({ HGUI_TAG_MAIN }, hgui::effects::BLURRED);
}

void ShapeDrawer::option_menu()
{
	if (hgui::KeyBoardManager::is_bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE)))
	{
		hgui::KeyBoardManager::unbind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE));
	}
	hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), [&]() { draw(); });
	hgui::Widget::active({ "option" });
	hgui::Renderer::draw({ "option" });
	hgui::Renderer::draw({ "draw" }, hgui::effects::BLURRED);
}

void ShapeDrawer::set_main_menu()
{
	hgui::TagManager::set_current_tag("main_menu");
	m_texts.push_back(hgui::LabelManager::create("V 1.0", hgui::point(0), m_font,
		{ 25u,  HGUI_COLOR_WHITE, 1.0f }));
	m_texts.back()->set_position(hgui::point(99_em - m_texts.back()->get_size().width, 0));

	auto image = hgui::image_loader("assets/textures/ShapeDrawer.png");
	m_logo = hgui::SpriteManager::create(image, image->get_size(), hgui::point(0));
	m_logo->set_position(hgui::point(50_em) - image->get_size() / 2 - hgui::point(0, 30_em));

	m_texts.push_back(hgui::LabelManager::create("Press any key", hgui::point(0), m_font,
		{ 40u, HGUI_COLOR_WHITE, 1.0f }));
	m_texts.back()->set_position(hgui::point(50_em) - m_texts.back()->get_size() / 2 - hgui::point(0, 15_em));
	m_texts.push_back(hgui::LabelManager::create("to start.", hgui::point(0), m_font,
		{ 40u, HGUI_COLOR_WHITE, 1.0f }));
	m_texts.back()->set_position(hgui::point(50_em) - m_texts.back()->get_size() / 2 - hgui::point(0, 12_em) +
		hgui::point(0, m_texts[2]->get_size().height));

	auto start = [this](const hgui::keys& key, const hgui::actions& action)
	{
		if (action == hgui::actions::PRESS && key != hgui::keys::ESCAPE)
		{
			m_texts.clear();
			m_logo = nullptr;
			draw();
		}
	};
	hgui::KeyBoardManager::bind_key_callback(start);
}
