#pragma once

#include "Include.h"
#include "ShapeManager.h"

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
    DataManager(std::shared_ptr<ShapeManager> shapes);

    /*! @brief Load shape data from a file.
     *
     *  @param path The file path to load the shape data from.
     */
    void load(std::string path);

    /*! @brief Save shape data to a file.
     *
     *  @param path The file path to save the shape data to.
     */
    void save(std::string path);

private:
    std::shared_ptr<ShapeManager> m_shapes;    //!< A shared pointer to the ShapeManager instance.
    std::map<std::string, ShapeType> m_names; //!< Map shape type to a string.

    bool parseur(const std::string& line) const;
};
