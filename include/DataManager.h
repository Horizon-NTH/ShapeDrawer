#pragma once

#include "Include.h"
#include "Shape.h"

/*! @brief Class for managing shape data.
 *
 *  This class provides functionality to load and save shape data from/to a file.
 *  It is associated with a ShapeManager instance to access the shapes.
 */
class DataManager
{
public:
    /*! @brief Constructor for the DataManager class.
     *
     *  @param shapes A shared pointer to the ShapeManager instance.
     */
    explicit DataManager(const std::shared_ptr<hgui::kernel::Drawer>& shapes);

    /*! @brief Load shape data from a file.
     *
     *  @param path The file path to load the shape data from.
     */
    void load(const std::string& path);

    /*! @brief Save shape data to a file.
     *
     *  @param path The file path to save the shape data to.
     */
    void save(const std::string& path);

private:
    std::shared_ptr<hgui::kernel::Drawer> m_shapes;    //!< A shared pointer to the ShapeManager instance.
    std::map<std::string, ShapeType> m_names; //!< Map shape type to a string.
};
