#include "Tema1_Object2D.h"

#include <Core/Engine.h>

Mesh* Tema1_Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Tema1_Object2D::CreateLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1};

	if (!fill) {
		line->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(1);
	}

	line->InitFromData(vertices, indices);
	return line;
}

Mesh* Tema1_Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Tema1_Object2D::CreateBalloon(std::string name, glm::vec3 center, float radius, float verticesNo, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;
	double twopi = 6.283;
	vertices.push_back(VertexFormat(center, color));
	for (int i = 1; i <= verticesNo; i++) {
		glm::vec3 aux = center;
		aux.x = radius * cos(i * twopi / verticesNo) * (1.5f) + center.x;
		aux.y = radius * sin(i * twopi / verticesNo) * (2.0f) + center.y;
		vertices.push_back(VertexFormat(aux, color));
	}

	std::vector<unsigned short> indices((float)(verticesNo + 1));
	for (GLushort i = 0; i <= verticesNo; i++) {
		indices[i] = i;
	}

	Mesh* balloon = new Mesh(name);
	if (!fill) {
		balloon->SetDrawMode(GL_TRIANGLE_FAN);
	}
	else {
		for (int i = 0; i <= verticesNo; i++) {
			indices.push_back(i);
		}
	}

	balloon->InitFromData(vertices, indices);
	return balloon;
}

Mesh* Tema1_Object2D::CreateEllipse(std::string name, glm::vec3 center, float radius, float verticesNo, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;
	double twopi = 6.283;
	double pi = 3.1415;
	vertices.push_back(VertexFormat(center, color));
	for (int i = 1; i <= verticesNo; i++) {
		glm::vec3 aux = center;
		aux.x = radius * sin(i * pi / verticesNo) * (0.75f) + center.x;
		aux.y = radius * cos(i * pi / verticesNo) * (1.0f) + center.y;
		vertices.push_back(VertexFormat(aux, color));
	}

	std::vector<unsigned short> indices(verticesNo + 1);
	for (int i = 0; i <= verticesNo; i++) {
		indices[i] = i;
	}

	Mesh* circle = new Mesh(name);
	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}
	else{
		for (int i = 0; i <= verticesNo; i++) {
			indices.push_back(i);
		}
	}

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Tema1_Object2D::CreateTriangleHorizontal(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, -height, 0), color),
		VertexFormat(corner + glm::vec3(width, -(height/2), 0.f), color)

	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;

}

Mesh* Tema1_Object2D::CreateBalloonHole(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width/2, height, 0), color),
	};

	Mesh* hole = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		hole->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
	}

	hole->InitFromData(vertices, indices);
	return hole;

}

Mesh* Tema1_Object2D::CreateShurikken(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, height, 0), color),
		VertexFormat(corner + glm::vec3(-width, height, 0), color),
		VertexFormat(corner , color),
		VertexFormat(corner + glm::vec3(-width, 0, 0), color),
		VertexFormat(corner + glm::vec3(-width, -height, 0), color),
		VertexFormat(corner , color),
		VertexFormat(corner + glm::vec3(0, -height, 0), color),
		VertexFormat(corner + glm::vec3(width, -height, 0), color),
		VertexFormat(corner , color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),

	};

	Mesh* shurikken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	if (!fill) {
		shurikken->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
	}

	shurikken->InitFromData(vertices, indices);
	return shurikken;

}

Mesh* Tema1_Object2D::CreateBalloonTail(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length, -length, 0), color),
		VertexFormat(corner + glm::vec3(0, -2*length, 0), color),
		VertexFormat(corner + glm::vec3(-length, -3*length, 0), color),
		VertexFormat(corner + glm::vec3(0, -4*length, 0), color),
	};

	Mesh* balloon_tail = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4 };

	if (!fill) {
		balloon_tail->SetDrawMode(GL_LINE_STRIP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(1);
	}

	balloon_tail->InitFromData(vertices, indices);
	return balloon_tail;
}

Mesh* Tema1_Object2D::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float width, float height, float peak_length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, height, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(width, peak_length / 2 + height / 2, 0), color),
		VertexFormat(corner + glm::vec3(width + sqrt(3)*(1.0f / 2.0f)* peak_length, height / 2, 0), color),
		VertexFormat(corner + glm::vec3(width, -peak_length/2 + height / 2, 0), color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3, 4, 5, 6 };

	if (!fill) {
		arrow->SetDrawMode(GL_TRIANGLE_FAN);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	arrow->InitFromData(vertices, indices);
	return arrow;
}
