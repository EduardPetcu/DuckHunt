#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    //Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float length, float length2, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCross(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateBar(const std::string &name, glm::vec3 leftBottomCorner, float length, float length2, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string &name, glm::vec3 leftBottomCorner, float length, float length2, glm::vec3 color, glm::vec3 color2, glm::vec3 color3, bool fill = false);

}
