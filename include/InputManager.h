#pragma once

#include "Include.h"
#include "ShapeDrawer.h"

typedef std::tuple<ShapeType, cv::Scalar, int> ShapeToDraw;
class ShapeDrawer;

/*! @brief Class responsible for handling user input.
 *
 *  This class provides static functions for initializing the input manager, handling key and mouse callbacks,
 *  and drawing shapes based on user input.
 */
class InputManager
{
public:
    /*! @brief Initialize the input manager with the given ShapeDrawer application.
     *
     *  @param app A pointer to the ShapeDrawer application.
     */
    static void init(ShapeDrawer* app);

    /*! @brief Handle key callbacks.
     *
     *  This function is called when a key event occurs and performs the necessary actions based on the key pressed.
     */
    static void key_callback();

    /*! @brief Handle mouse callbacks.
     *
     *  @param event The mouse event that occurred.
     *  @param x The x-coordinate of the mouse position.
     *  @param y The y-coordinate of the mouse position.
     *  @param flags Additional flags associated with the mouse event.
     *  @param userdata Additional user data.
     */
    static void mouse_callback(int event, int x, int y, int flags, void* userdata);

    /*! @brief Draw shapes based on user input.
     *
     *  This function is called to draw shapes on the window based on the user's input.
     */
    static void draw();

private:
    InputManager();                                 //!< Private constructor to prevent object creation.

    static ShapeDrawer* m_app;                      //!< Pointer to the ShapeDrawer application.
    static ShapeToDraw m_toDraw;                    //!< The shape to be drawn based on user input.
    static bool m_randomDrawing;                    //!< Flag indicating whether random drawing is enabled.
    static std::vector<cv::Point> m_shapeDrawn;     //!< Vector containing the points of the shape drawn by the user.
    static cv::Point m_cursorPosition;              //!< The current position of the cursor.
};
