#include "../include/ShapeDrawer.h"

#include "hgui/header/Vector.hpp"
#include "hgui/header/Vector.hpp"

ShapeDrawer::ShapeDrawer() : m_window(nullptr),
                             m_monitor(nullptr),
                             m_font(nullptr),
                             m_dataManager(nullptr),
                             m_logo(nullptr),
                             m_canvas(nullptr),
                             m_toDraw(ShapeToDraw(shape::CIRCLE, HGUI_COLOR_BLUE, 20.f, false)),
                             m_randomDrawing
                             (false)
{
	// Library initialization //
	hgui::init();
	// Window creation //
	m_monitor = hgui::MonitorManager::get_primary_monitor();
	m_window = hgui::WindowManager::create("ShapeDrawer", m_monitor->get_size(),
	                                       hgui::point(0), hgui::image_loader("assets/textures/logo.png"), nullptr, {
		                                       hgui::WindowOption(hgui::options::MAXIMIZED, true)
	                                       });
	// Tag creation //
	hgui::TagManager::create_tag("main_menu");
	hgui::TagManager::create_tag("draw");
	hgui::TagManager::create_tag("option");
	// Load Font //
	m_font = hgui::FontManager::create("assets/fonts/montserrat/Montserrat-Regular.otf");
	// Binding //
	hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), hgui::end);
	// Create canvas //
	hgui::TagManager::set_current_tag("draw");
	m_canvas = hgui::CanvasManager::create(nullptr, m_window->get_size(), hgui::point(0), HGUI_COLOR_BLACK);
	set_main_menu();
	set_option_menu();
}

void ShapeDrawer::start() const
{
	m_canvas->get_drawer()->get_shapes()->clear();
	draw_background();
	hgui::Widget::active({"main_menu"});
	hgui::Renderer::draw({"main_menu"});
	hgui::Renderer::draw({"draw"}, hgui::effects::BLURRED);
	hgui::Renderer::loop();
}

const std::shared_ptr<DataManager>& ShapeDrawer::get_dataManager() const
{
	return m_dataManager;
}

void ShapeDrawer::draw()
{
	if (hgui::KeyBoardManager::is_bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE)))
	{
		hgui::KeyBoardManager::unbind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE));
	}
	hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), [&] { option_menu(); });
	hgui::Renderer::set_draw_callback([this] { draw_shape(); });
	hgui::Widget::active({"draw"});
	hgui::Renderer::draw({"draw"});
	hgui::Renderer::draw({HGUI_TAG_MAIN}, hgui::effects::BLURRED);
}

void ShapeDrawer::option_menu()
{
	if (hgui::KeyBoardManager::is_bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE)))
	{
		hgui::KeyBoardManager::unbind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE));
	}
	m_shapeDrawn.clear();
	hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), [&] { draw(); });
	hgui::Widget::active({"option"});
	hgui::Renderer::draw({"option"});
	hgui::Renderer::draw({"draw"}, hgui::effects::BLURRED);
}

void ShapeDrawer::draw_shape()
{
	typedef std::tuple<shape, hgui::color, float, bool> ShapeToDraw;
	if (!m_randomDrawing)
	{
		switch (std::get<0>(m_toDraw))
		{
		case shape::LINE:
			if (m_shapeDrawn.size() == 2)
			{
				m_canvas->get_drawer()->draw_line(m_shapeDrawn.at(0), m_shapeDrawn.at(1), std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			else if (m_shapeDrawn.size() == 1)
			{
				const hgui::kernel::shape::StraightLine line(m_shapeDrawn.at(0), hgui::MouseManager::get_position(), std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				line.draw(m_canvas->get_position(), m_canvas->get_size());
			}
			break;
		case shape::CIRCLE:
			if (m_shapeDrawn.size() == 2)
			{
				m_canvas->get_drawer()->draw_circle(m_shapeDrawn.at(0), hgui::kernel::distance(m_shapeDrawn.at(0), m_shapeDrawn.at(1)), std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			else if (m_shapeDrawn.size() == 1)
			{
				const hgui::kernel::shape::Circle circle(m_shapeDrawn.at(0), hgui::kernel::distance(m_shapeDrawn.at(0), hgui::point(hgui::MouseManager::get_position())), std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
				circle.draw(m_canvas->get_position(), m_canvas->get_size());
			}
			break;
		case shape::RECTANGLE:
			if (m_shapeDrawn.size() == 2)
			{
				m_canvas->get_drawer()->draw_rectangle(m_shapeDrawn.at(0), m_shapeDrawn.at(1), std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			else if (m_shapeDrawn.size() == 1)
			{
				const hgui::kernel::shape::Rectangle rectangle(m_shapeDrawn.at(0), hgui::MouseManager::get_position(), std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
				rectangle.draw(m_canvas->get_position(), m_canvas->get_size());
			}
			break;
		case shape::TRIANGLE:
			if (m_shapeDrawn.size() == 1)
			{
				const hgui::kernel::shape::StraightLine line(m_shapeDrawn.at(0), hgui::MouseManager::get_position(), std::get<1>(m_toDraw), std::get<2>(m_toDraw));
				line.draw(m_canvas->get_position(), m_canvas->get_size());
			}
			else if (m_shapeDrawn.size() == 2)
			{
				const hgui::kernel::shape::Triangle triangle(m_shapeDrawn.at(0), m_shapeDrawn.at(1), hgui::MouseManager::get_position(), std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
				triangle.draw(m_canvas->get_position(), m_canvas->get_size());
			}
			else if (m_shapeDrawn.size() == 3)
			{
				m_canvas->get_drawer()->draw_triangle(m_shapeDrawn.at(0), m_shapeDrawn.at(1), m_shapeDrawn.at(2), std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
				m_shapeDrawn.clear();
			}
			break;
		}
	}
}

void ShapeDrawer::draw_background() const
{
	const auto& shapes = m_canvas->get_drawer()->get_shapes();
	const auto randomPoint = [&]() -> hgui::point
		{
			const hgui::size windowSize = m_window->get_size();
			return {
						std::rand() % static_cast<int>(windowSize.width),
						std::rand() % static_cast<int>(windowSize.height)
					};
		};
	if (hgui::random(0.7) || shapes->empty())
	{
		switch (static_cast<shape>(std::rand() % 4))
		{
		case shape::RECTANGLE:
			m_canvas->get_drawer()->draw_rectangle(randomPoint(), randomPoint(), hgui::color(
				                                       static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX),
			                                       hgui::random(0.5), static_cast<float>(std::rand() % 99 + 1));
			break;
		case shape::TRIANGLE:
			m_canvas->get_drawer()->draw_triangle(randomPoint(), randomPoint(), randomPoint(), hgui::color(
				                                      static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX),
			                                      hgui::random(0.5), static_cast<float>(std::rand() % 99 + 1));
			break;
		case shape::CIRCLE:
			m_canvas->get_drawer()->draw_circle(randomPoint(), static_cast<float>(std::rand() % 1000), hgui::color(
				                                    static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX),
			                                    hgui::random(0.5), static_cast<float>(std::rand() % 99 + 1));
			break;
		case shape::LINE:
			m_canvas->get_drawer()->draw_line(randomPoint(), randomPoint(), hgui::color(
				                                  static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX),
			                                  static_cast<float>(std::rand() % 99 + 1));
			break;
		}
	}
	else
	{
		shapes->erase(shapes->begin() + std::rand() % shapes->size());
	}
	hgui::TaskManager::program(std::chrono::milliseconds(500), [this] { draw_background(); });
}

void ShapeDrawer::set_main_menu()
{
	hgui::TagManager::set_current_tag("main_menu");
	m_texts.push_back(hgui::LabelManager::create("V 1.0", hgui::point(0), m_font,
	                                             {25u, HGUI_COLOR_WHITE, 1.0f}));
	m_texts.back()->set_position(hgui::point(99_em - m_texts.back()->get_size().width, 1_em));

	auto image = hgui::image_loader("assets/textures/ShapeDrawer.png");
	m_logo = hgui::SpriteManager::create(image, image->get_size(), hgui::point(0));
	m_logo->set_position(hgui::point(50_em) - image->get_size() / 2 - hgui::point(0, 20_em));

	m_texts.push_back(hgui::LabelManager::create("Press any key", hgui::point(0), m_font,
	                                             {100u, HGUI_COLOR_WHITE, 1.0f}));
	m_texts.back()->set_position(hgui::point(50_em) - m_texts.back()->get_size() / 2 + hgui::point(0, 10_em));
	m_texts.push_back(hgui::LabelManager::create("to start.", hgui::point(0), m_font,
	                                             {100u, HGUI_COLOR_WHITE, 1.0f}));
	m_texts.back()->set_position(hgui::point(50_em) - m_texts.back()->get_size() / 2 + hgui::point(0, 12_em) +
		hgui::point(0, m_texts[2]->get_size().height));

	auto start = [this](const hgui::keys& key, const hgui::actions& action)
		{
			if (action == hgui::actions::PRESS && key != hgui::keys::ESCAPE)
			{
				m_canvas->get_drawer()->get_shapes()->clear();
				m_texts.clear();
				m_logo = nullptr;
				set_input();
				hgui::TaskManager::deprogram(hgui::TaskManager::get_ids().at(0));
				hgui::KeyBoardManager::bind_key_callback([]
					{
					});
				draw();
			}
		};
	hgui::KeyBoardManager::bind_key_callback(start);
}

void ShapeDrawer::set_option_menu()
{
	hgui::TagManager::set_current_tag("option");
	constexpr int BUTTON_SIZE = 100;
	constexpr int GAP = 15;
	const auto get_position = [](const int row, const int columns) -> hgui::point
		{
			return {5_em + (columns - 1) * (BUTTON_SIZE + GAP), 5_em + (row - 1) * (BUTTON_SIZE + GAP)};
		};
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                draw();
		                                                }, hgui::size(BUTTON_SIZE), get_position(1, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/option.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                m_canvas->unbind(hgui::MouseAction(hgui::buttons::LEFT, hgui::actions::PRESS));
			                                                m_canvas->unbind(hgui::MouseAction(hgui::buttons::RIGHT, hgui::actions::PRESS));
			                                                m_canvas->unbind(hgui::inputs::SCROLL_UP);
			                                                m_canvas->unbind(hgui::inputs::SCROLL_DOWN);
			                                                hgui::KeyBoardManager::unbind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE));
			                                                hgui::KeyBoardManager::bind(hgui::KeyBoardAction(hgui::keys::ESCAPE, hgui::actions::RELEASE), hgui::end);
			                                                set_main_menu();
			                                                start();
		                                                }, hgui::size(BUTTON_SIZE), get_position(1, 2),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/home.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                hgui::end();
		                                                }, hgui::size(BUTTON_SIZE), get_position(1, 3),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/exit.png"))));

	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                m_randomDrawing = true;
		                                                }, hgui::size(BUTTON_SIZE), get_position(2, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/random.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                m_randomDrawing = false;
		                                                }, hgui::size(BUTTON_SIZE), get_position(2, 2),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/pen.png"))));

	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                if (const auto& shapes = m_canvas->get_drawer()->get_shapes(); !shapes->empty())
			                                                {
				                                                shapes->pop_back();
			                                                }
		                                                }, hgui::size(BUTTON_SIZE), get_position(3, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/delete.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                const auto& shapes = m_canvas->get_drawer()->get_shapes();
			                                                shapes->clear();
		                                                }, hgui::size(BUTTON_SIZE), get_position(3, 2),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/clear.png"))));

	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<0>(m_toDraw) = static_cast<shape>(std::rand() % 4);
		                                                }, hgui::size(BUTTON_SIZE), get_position(4, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/random.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<0>(m_toDraw) = shape::LINE;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(4, 2),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/line.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<0>(m_toDraw) = shape::CIRCLE;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(4, 3),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/circle.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<0>(m_toDraw) = shape::RECTANGLE;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(4, 4),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/rectangle.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<0>(m_toDraw) = shape::TRIANGLE;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(4, 5),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/triangle.png"))));

	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<1>(m_toDraw) = hgui::color(
				                                                static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX, static_cast<float>(std::rand()) / RAND_MAX);
		                                                }, hgui::size(BUTTON_SIZE), get_position(5, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/random.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<1>(m_toDraw) = HGUI_COLOR_RED;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(5, 2), nullptr, HGUI_COLOR_RED, 20.f));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<1>(m_toDraw) = HGUI_COLOR_GREEN;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(5, 3), nullptr, HGUI_COLOR_GREEN, 20.f));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<1>(m_toDraw) = HGUI_COLOR_BLUE;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(5, 4), nullptr, HGUI_COLOR_BLUE, 20.f));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<1>(m_toDraw) = HGUI_COLOR_WHITE;
		                                                }, hgui::size(BUTTON_SIZE),
	                                                get_position(5, 5), nullptr, HGUI_COLOR_WHITE, 20.f));

	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<2>(m_toDraw) = std::max(std::get<2>(m_toDraw) - 5.f, 1.f);
		                                                }, hgui::size(BUTTON_SIZE), get_position(6, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/minus.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<2>(m_toDraw) += 5.f;
		                                                }, hgui::size(BUTTON_SIZE), get_position(6, 2),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/plus.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<3>(m_toDraw) = false;
		                                                }, hgui::size(BUTTON_SIZE), get_position(7, 1),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/unfill.png"))));
	m_buttons.push_back(hgui::ButtonManager::create([&]
		                                                {
			                                                std::get<3>(m_toDraw) = true;
		                                                }, hgui::size(BUTTON_SIZE), get_position(7, 2),
	                                                hgui::TextureManager::create(hgui::image_loader("assets/textures/fill.png"))));
}

void ShapeDrawer::set_input()
{
	const auto isPointIn = [](const shape type, const hgui::kernel::shape::ShapeData& data, const hgui::point& point) -> bool
		{
			switch (type)
			{
			case shape::RECTANGLE:
				if (const auto points = std::get_if<std::pair<hgui::point, hgui::point>>(&data))
				{
					const hgui::point A = points->first, B = hgui::point(points->second.x, points->first.y), D = hgui::point(
						                  points->first.x, points->second.y);
					const auto dotAMAB = hgui::kernel::dot(point - A, B - A), dotAMAD = hgui::kernel::dot(point - A, D - A);
					return (0 < dotAMAB && dotAMAB < hgui::kernel::dot(B - A, B - A)) && (0 < dotAMAD && dotAMAD < hgui::kernel::dot(
						D - A, D - A));
				}
				break;
			case shape::TRIANGLE:
				if (const auto points = std::get_if<std::array<hgui::point, 3>>(&data))
				{
					auto area = [](const hgui::point& v1, const hgui::point& v2, const hgui::point& v3) -> double
						{
							return std::abs((v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0);
						};
					hgui::point v1 = points->at(0), v2 = points->at(1), v3 = points->at(2);
					return area(point, v1, v2) + area(point, v2, v3) + area(point, v3, v1) - area(v1, v2, v3) < 1e-6;
				}
				break;
			case shape::CIRCLE:
				if (const auto points = std::get_if<std::pair<hgui::point, HGUI_PRECISION>>(&data))
				{
					return hgui::kernel::distance(point, points->first) <= points->second;
				}
				break;
			case shape::LINE:
				if (const auto points = std::get_if<std::tuple<hgui::point, hgui::point, HGUI_PRECISION>>(&data))
				{
					const HGUI_PRECISION a = std::get<1>(*points).y - std::get<0>(*points).y;
					const HGUI_PRECISION b = std::get<0>(*points).x - std::get<1>(*points).x;
					const HGUI_PRECISION c = std::get<1>(*points).x * std::get<0>(*points).y - std::get<0>(*points).x * std::get<1>(*points).y;
					const bool nearPoint = hgui::kernel::distance(std::get<0>(*points), point) <= std::get<2>(*points) / 2.0f ||
							hgui::kernel::distance(std::get<1>(*points), point) <= std::get<2>(*points) / 2.0f;
					if (std::abs(a) < 1e-6f)
					{
						return nearPoint || (point.x >= std::min(std::get<0>(*points).x, std::get<1>(*points).x) &&
							point.x <= std::max(std::get<0>(*points).x, std::get<1>(*points).x) &&
							std::abs(std::get<0>(*points).y - point.y) <= std::get<2>(*points) / 2.0f);
					}
					else if (std::abs(b) < 1e-6f)
					{
						return nearPoint || (point.y >= std::min(std::get<0>(*points).y, std::get<1>(*points).y) &&
							point.y <= std::max(std::get<0>(*points).y, std::get<1>(*points).y) &&
							std::abs(std::get<0>(*points).x - point.x) <= std::get<2>(*points) / 2.0f);
					}
					else
					{
						return nearPoint ||
						(std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b) <= std::get<2>(*points) / 2.0f &&
							point.x >= std::min(std::get<0>(*points).x, std::get<1>(*points).x) &&
							point.x <= std::max(std::get<0>(*points).x, std::get<1>(*points).x) &&
							point.y >= std::min(std::get<0>(*points).y, std::get<1>(*points).y) &&
							point.y <= std::max(std::get<0>(*points).y, std::get<1>(*points).y));
					}
				}
				break;
			}
			return false;
		};
	m_canvas->bind(hgui::MouseAction(hgui::buttons::LEFT, hgui::actions::PRESS), [&]
		               {
			               const auto click = hgui::point(hgui::MouseManager::get_position().x, hgui::MouseManager::get_position().y);
			               const auto randomPoint = [&]() -> hgui::point
				               {
					               const hgui::size windowSize = m_window->get_size();
					               return {
								               std::rand() % static_cast<int>(windowSize.width),
								               std::rand() % static_cast<int>(windowSize.height)
							               };
				               };
			               if (m_randomDrawing)
			               {
				               switch (std::get<0>(m_toDraw))
				               {
				               case shape::RECTANGLE:
					               {
						               hgui::point firstPoint, secondPoint;
						               do
						               {
							               firstPoint = randomPoint();
							               secondPoint = randomPoint();
						               } while (!isPointIn(shape::RECTANGLE, std::make_pair(firstPoint, secondPoint), click));
						               m_canvas->get_drawer()->draw_rectangle(firstPoint, secondPoint,
						                                                      std::get<1>(m_toDraw), std::get<3>(m_toDraw),
						                                                      std::get<2>(m_toDraw));
					               }
					               break;
				               case shape::CIRCLE:
					               m_canvas->get_drawer()->draw_circle(click,
					                                                   static_cast<float>(std::rand() % static_cast<int>(m_canvas->
					                                                                                                     get_size().height / 2.0f)),
					                                                   std::get<1>(m_toDraw), std::get<3>(m_toDraw), std::get<2>(m_toDraw));
					               break;
				               case shape::TRIANGLE:
					               {
						               hgui::point firstPoint, secondPoint, thirdPoint;
						               do
						               {
							               firstPoint = randomPoint();
							               secondPoint = randomPoint();
							               thirdPoint = randomPoint();
						               } while (!isPointIn(shape::TRIANGLE,
						                                   std::array{firstPoint, secondPoint, thirdPoint}, click));
						               m_canvas->get_drawer()->draw_triangle(firstPoint, secondPoint, thirdPoint,
						                                                     std::get<1>(m_toDraw), std::get<3>(m_toDraw),
						                                                     std::get<2>(m_toDraw));
					               }
					               break;
				               case shape::LINE:
					               {
						               hgui::point firstPoint, secondPoint;
						               do
						               {
							               firstPoint = randomPoint();
							               secondPoint = randomPoint();
						               } while (!isPointIn(shape::LINE, std::tuple(firstPoint, secondPoint, std::get<2>(m_toDraw)),
						                                   click));
						               m_canvas->get_drawer()->draw_line(firstPoint, secondPoint,
						                                                 std::get<1>(m_toDraw), std::get<2>(m_toDraw));
					               }
					               break;
				               }
			               }
			               else
			               {
				               m_shapeDrawn.push_back(click);
			               }
		               });
	m_canvas->bind(hgui::MouseAction(hgui::buttons::RIGHT, hgui::actions::PRESS), [&]
		               {
			               const auto click = hgui::point(hgui::MouseManager::get_position().x, hgui::MouseManager::get_position().y);
			               if (m_randomDrawing || m_shapeDrawn.empty())
			               {
				               auto& shapes = m_canvas->get_drawer()->get_shapes();
				               if (const auto shapeToDelete = std::find_if(shapes->rbegin(), shapes->rend(),
				                                                           [&](const std::shared_ptr<hgui::kernel::shape::Shape>& shape) ->
			                                                           bool
					                                                           {
						                                                           if (const auto data = std::get_if<std::pair<
							                                                           hgui::point, hgui::point>>(&shape->get_data()))
						                                                           {
							                                                           if (!shape->is_fill())
							                                                           {
								                                                           const hgui::point topLeftVertex = hgui::point(
									                                                                             std::min(std::get<0>(*data).x,
									                                                                                      std::get<1>(*data).x),
									                                                                             std::min(std::get<0>(*data).y,
									                                                                                      std::get<1>(*data).y)),
								                                                                             bottomRightVertex = hgui::point(
									                                                                             std::max(std::get<0>(*data).x,
									                                                                                      std::get<1>(*data).x),
									                                                                             std::max(std::get<0>(*data).y,
									                                                                                      std::get<1>(*data).y));
								                                                           return isPointIn(shape::LINE, std::make_tuple(topLeftVertex, hgui::point(bottomRightVertex.x, topLeftVertex.y), shape->get_thickness()), click) ||
										                                                           isPointIn(shape::LINE, std::make_tuple(hgui::point(bottomRightVertex.x, topLeftVertex.y), bottomRightVertex, shape->get_thickness()), click) ||
										                                                           isPointIn(shape::LINE, std::make_tuple(bottomRightVertex, hgui::point(topLeftVertex.x, bottomRightVertex.y), shape->get_thickness()), click) ||
										                                                           isPointIn(shape::LINE, std::make_tuple(hgui::point(topLeftVertex.x, bottomRightVertex.y), topLeftVertex, shape->get_thickness()), click);
							                                                           }
							                                                           return isPointIn(shape::RECTANGLE, *data, click);
						                                                           }
						                                                           else if (const auto data = std::get_if<std::pair<
							                                                           hgui::point, HGUI_PRECISION>>(&shape->get_data()))
						                                                           {
							                                                           if (!shape->is_fill())
							                                                           {
								                                                           return isPointIn(
											                                                           shape::CIRCLE,
											                                                           std::make_pair(
												                                                           std::get<0>(*data),
												                                                           std::get<1>(*data) + shape->
												                                                           get_thickness()), click) &&
										                                                           !isPointIn(shape::CIRCLE,
										                                                                      std::make_pair(
											                                                                      std::get<0>(*data),
											                                                                      std::get<1>(*data) - shape->
											                                                                      get_thickness()), click);
							                                                           }
							                                                           return isPointIn(shape::CIRCLE, *data, click);
						                                                           }
						                                                           else if (const auto data = std::get_if<std::array<
							                                                           hgui::point, 3>>(&shape->get_data()))
						                                                           {
							                                                           if (!shape->is_fill())
							                                                           {
								                                                           return isPointIn(shape::LINE, std::make_tuple(data->at(0), data->at(1), shape->get_thickness()), click) ||
										                                                           isPointIn(shape::LINE, std::make_tuple(data->at(1), data->at(2), shape->get_thickness()), click) ||
										                                                           isPointIn(shape::LINE, std::make_tuple(data->at(2), data->at(0), shape->get_thickness()), click);
							                                                           }
							                                                           return isPointIn(shape::TRIANGLE, *data, click);
						                                                           }
						                                                           else if (const auto data = std::get_if<std::tuple<
							                                                           hgui::point, hgui::point, HGUI_PRECISION>>(
							                                                           &shape->get_data()))
						                                                           {
							                                                           return isPointIn(shape::LINE, *data, click);
						                                                           }
						                                                           return false;
					                                                           }); shapeToDelete != shapes->rend())
				               {
					               shapes->erase(std::prev(shapeToDelete.base()));
				               }
			               }
			               else
			               {
				               m_shapeDrawn.clear();
			               }
		               });
	m_canvas->bind(hgui::inputs::SCROLL_UP, [&]
		               {
			               std::get<2>(m_toDraw) += 5.f;
		               });
	m_canvas->bind(hgui::inputs::SCROLL_DOWN, [&]
		               {
			               std::get<2>(m_toDraw) = std::max(std::get<2>(m_toDraw) - 5.f, 1.f);
		               });
}
