#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Tema1_Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateBalloonTail(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
	Mesh* CreateEllipse(std::string name, glm::vec3 center, float radius, float vericesNo, glm::vec3 color, bool fill = false);
	Mesh* CreateTriangleHorizontal(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
	Mesh* CreateBalloonHole(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
	Mesh* CreateBalloon(std::string name, glm::vec3 center, float radius, float vericesNo, glm::vec3 color, bool fill = false);
	Mesh* CreateShurikken(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
	Mesh* CreateArrow(std::string name, glm::vec3 leftBottomCorner, float width, float height, float peak_length, glm::vec3 color, bool fill = false);

}

