#pragma once

#include "Include.h"
#include "ShapeManager.h"
#include "InputManager.h"
#include "DataManager.h"

/*! @brief Class for drawing shapes on a window.
 *
 *  This class provides functionality to create a window, manage shapes, and draw them on the window.
 *  It also handles user input and provides a main menu for interaction.
 */
class ShapeDrawer
{
public:
    /*! @brief Constructor for the ShapeDrawer class.
     *
     *  @param windowSize The size of the window to be created.
     */
    ShapeDrawer(cv::Size windowSize = cv::Size(1920, 1080));

    /*! @brief Run the shape drawing application.
     *
     *  This function starts the main loop of the application, handling user input and drawing shapes on the window.
     */
    void run() const;

    /*! @brief Get the window associated with the ShapeDrawer.
     *
     *  @return A shared pointer to the window.
     */
    const std::shared_ptr<Window>& get_window() const;

    /*! @brief Get the ShapeManager associated with the ShapeDrawer.
     *
     *  @return A shared pointer to the ShapeManager.
     */
    const std::shared_ptr<ShapeManager>& get_shapeManager() const;

    /*! @brief Get the DataManager associated with the ShapeDrawer.
     *
     *  @return A shared pointer to the DataManager.
     */
    const std::shared_ptr<DataManager>& get_dataManager() const;

    /*! @brief Close the ShapeDrawer application. */
    void close();

private:
    std::shared_ptr<Window> m_window;             //!< The window used for drawing shapes.
    std::shared_ptr<DataManager> m_data;          //!< The data manager for managing shape data.
    std::shared_ptr<ShapeManager> m_shapes;       //!< The shape manager for managing shapes.
    bool m_shouldClose;                          //!< Flag indicating whether the application should close.

    /*! @brief Display the main menu on the console.
     *
     *  This function prints the main menu options to the console.
     */
    void main_menu() const;
};
