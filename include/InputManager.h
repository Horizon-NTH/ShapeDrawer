#pragma once

#include "Include.h"

enum ShapeType
{
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    LINE
};

typedef std::variant<
    std::pair<hgui::point, hgui::point>,    // For rectangle and line
    std::pair<hgui::point, int>,          // For circle
    std::array<hgui::point, 3>,           // For triangle
    std::tuple<hgui::point, hgui::point, int>  // For line
> ShapeData;

typedef std::tuple<ShapeType, hgui::color, int> ShapeToDraw;
class ShapeDrawer;

class InputManager
{
public:
    static void init(ShapeDrawer* app);

    static void key_callback();

    static void mouse_callback(int event, int x, int y, int flags, void* userData);

    static void draw();

private:
    InputManager();

    static ShapeDrawer* m_app;
    static ShapeToDraw m_toDraw;
    static bool m_randomDrawing;
    static std::vector<hgui::point> m_shapeDrawn;
    static hgui::point m_cursorPosition;
};
