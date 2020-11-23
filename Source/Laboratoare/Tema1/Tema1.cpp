#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "../../../Visual Studio//Tema1_Transform2D.h"
#include "../../../Visual Studio/Tema1_Object2D.h"

#define PI 3.1415

using namespace std;

Tema1::Tema1() {}

Tema1::~Tema1() {}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;
	translateShurikken = 0;
	VelX = 75;
	translateBalloon = 0;
	VelY = 75;
	translateArrowX = 0;
	translateArrowY = 0;
	arrowSpeed = 0;
	bow_pos_up_corner = bow_posY + bow_radius;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;


	Mesh* Bow = Tema1_Object2D::CreateEllipse("Bow", glm::vec3(0, 0, 0), bow_radius, 1000, glm::vec3(1, 0, 0));
	AddMeshToList(Bow);

	Mesh* BowString = Tema1_Object2D::CreateLine("BowString", glm::vec3(0, 0, 0), 2*bow_radius, glm::vec3(1, 1, 0));
	AddMeshToList(BowString);

	Mesh* Arrow = Tema1_Object2D::CreateArrow("Arrow", glm::vec3(0, 0, 0), arrow_width, arrow_height, peak_length , glm::vec3(0, 1, 0), true);
	AddMeshToList(Arrow);

	Mesh* BalloonR = Tema1_Object2D::CreateBalloon("BalloonR", glm::vec3(0, 0, 0), 20, 1000, glm::vec3(1, 0, 0));
	AddMeshToList(BalloonR);

	Mesh* BalloonTailR = Tema1_Object2D::CreateBalloonTail("BalloonTailR", glm::vec3(0, 0, 0), 10, glm::vec3(1, 0, 0));
	AddMeshToList(BalloonTailR);

	Mesh* BalloonHoleR = Tema1_Object2D::CreateBalloonHole("BalloonHoleR", glm::vec3(0, 0, 0), 15, 15, glm::vec3(1, 0, 0), true);
	AddMeshToList(BalloonHoleR);

	Mesh* BalloonY = Tema1_Object2D::CreateBalloon("BalloonY", glm::vec3(0, 0, 0), 20, 1000, glm::vec3(1, 1, 0));
	AddMeshToList(BalloonY);

	Mesh* BalloonTailY = Tema1_Object2D::CreateBalloonTail("BalloonTailY", glm::vec3(0, 0, 0), 10, glm::vec3(1, 1, 0));
	AddMeshToList(BalloonTailY);

	Mesh* BalloonHoleY = Tema1_Object2D::CreateBalloonHole("BalloonHoleY", glm::vec3(0, 0, 0), 15, 15, glm::vec3(1, 1, 0), true);
	AddMeshToList(BalloonHoleY);

	Mesh* shurikken = Tema1_Object2D::CreateShurikken("shurikken", glm::vec3(0, 0, 0), 30, 30, glm::vec3(105, 105, 105), true);
	AddMeshToList(shurikken);

}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	width = resolution.x;
	height = resolution.y;
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(arrow_posX, arrow_posY);

		if (Release == false) {
			modelMatrix *= Tema1_Transform2D::Translate(translateX, translateY);
			modelMatrix *= Tema1_Transform2D::Rotate(angularStepBow);
			RenderMesh2D(meshes["Arrow"], shaders["VertexColor"], modelMatrix);
		}
		else {
			translateArrowX += arrowSpeed * deltaTimeSeconds;
			modelMatrix *= Tema1_Transform2D::Rotate(angularStepArrow);
			modelMatrix *= Tema1_Transform2D::Translate(translateArrowX, translateArrowY);
			RenderMesh2D(meshes["Arrow"], shaders["VertexColor"], modelMatrix);

			if (translateArrowX >= 1200) {
				Release = false;
				translateArrowX = arrow_posX;
				arrow_posY = bow_posY;
				arrowSpeed = 0;
			}
		}
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(bow_posX, bow_posY - bow_radius);
		modelMatrix *= Tema1_Transform2D::Translate(translateX, translateY);
		modelMatrix *= Tema1_Transform2D::Translate(0, bow_radius);
		modelMatrix *= Tema1_Transform2D::Rotate(angularStepBow);
		modelMatrix *= Tema1_Transform2D::Translate(0, -bow_radius);
		RenderMesh2D(meshes["BowString"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(bow_posX, bow_posY - bow_radius);
		modelMatrix *= Tema1_Transform2D::Translate(translateX, translateY);
		modelMatrix *= Tema1_Transform2D::Translate(0, bow_radius);
		modelMatrix *= Tema1_Transform2D::Rotate(angularStepBow);
		RenderMesh2D(meshes["Bow"], shaders["VertexColor"], modelMatrix);
	}
	{
		translateShurikken += VelX * 1.2f *deltaTimeSeconds;
		angularStep += 2.0f * deltaTimeSeconds;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(-translateShurikken, 0);
		modelMatrix *= Tema1_Transform2D::Translate(1200, 200);
		modelMatrix *= Tema1_Transform2D::Translate(0 , 0 );
		modelMatrix *= Tema1_Transform2D::Rotate(angularStep);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		RenderMesh2D(meshes["shurikken"], shaders["VertexColor"], modelMatrix);
	}
	{
		translateShurikken2 += VelX * 1.2f * deltaTimeSeconds;
		angularStep2 += 2.0f * deltaTimeSeconds;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(-translateShurikken2, 0);
		modelMatrix *= Tema1_Transform2D::Translate(1600, 400);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		modelMatrix *= Tema1_Transform2D::Rotate(angularStep2);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		RenderMesh2D(meshes["shurikken"], shaders["VertexColor"], modelMatrix);
	}
	{
		translateShurikken3 += VelX * 1.2f * deltaTimeSeconds;
		angularStep3 += 2.0f * deltaTimeSeconds;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(-translateShurikken3, 0);
		modelMatrix *= Tema1_Transform2D::Translate(2000, 100);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		modelMatrix *= Tema1_Transform2D::Rotate(angularStep3);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		RenderMesh2D(meshes["shurikken"], shaders["VertexColor"], modelMatrix);
	}
	{
		translateShurikken4 += VelX * 1.2f * deltaTimeSeconds;
		angularStep4 += 2.0f * deltaTimeSeconds;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(-translateShurikken4, 0);
		modelMatrix *= Tema1_Transform2D::Translate(2400, 550);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		modelMatrix *= Tema1_Transform2D::Rotate(angularStep4);
		modelMatrix *= Tema1_Transform2D::Translate(0, 0);
		RenderMesh2D(meshes["shurikken"], shaders["VertexColor"], modelMatrix);
	}
	{
		translateBalloon += VelY  * deltaTimeSeconds;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(600, translateBalloon - 700);
		RenderMesh2D(meshes["BalloonR"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-600, -300);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(592, translateBalloon - 745);
		RenderMesh2D(meshes["BalloonHoleR"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(600, translateBalloon - 745); 
		RenderMesh2D(meshes["BalloonTailR"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-600, -305);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(1000, translateBalloon - 400);
		RenderMesh2D(meshes["BalloonR"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-1000, -300);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(992, translateBalloon - 445); 
		RenderMesh2D(meshes["BalloonHoleR"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(1000, translateBalloon - 445);
		RenderMesh2D(meshes["BalloonTailR"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-1000, -305);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(400, translateBalloon - 100);
		RenderMesh2D(meshes["BalloonY"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-400, -300);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(392, translateBalloon - 145);
		RenderMesh2D(meshes["BalloonHoleY"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(400, translateBalloon - 145);
		RenderMesh2D(meshes["BalloonTailY"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-400, -305);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(800, translateBalloon - 1000);
		RenderMesh2D(meshes["BalloonY"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-800, -300);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(792, translateBalloon - 1045);
		RenderMesh2D(meshes["BalloonHoleY"], shaders["VertexColor"], modelMatrix);
	}
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Tema1_Transform2D::Translate(800, translateBalloon - 1045);
		RenderMesh2D(meshes["BalloonTailY"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Tema1_Transform2D::Translate(-800, -305);
	}
}

void Tema1::FrameEnd(){}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	glm::ivec2 resolution = window->GetResolution();
	
	if (window->KeyHold(GLFW_KEY_W) && (translateY + bow_pos_up_corner <= height))
	{
		translateY += 200 * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S) && (translateY + 2.6f*bow_radius >= 0))
	{
		translateY -= 200 * deltaTime;
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
		if (bow_posY == arrow_posY) {
			Hold = true;
			arrowSpeed += 10.0f;
		}
	}
	else if (Hold == true) {
		Hold = false;
		Release = true;
		angularStepArrow = angularStepBow;
		translateArrowY = translateY + bow_posY;
		arrow_posY = 0;
	}
}

void Tema1::OnKeyPress(int key, int mods){}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{	
	glm::ivec2 resolution = window->GetResolution();
	angularStepBow = glm::atan((float)(resolution.y - bow_posY - mouseY - translateY), (float)(mouseX - bow_posX));
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}
