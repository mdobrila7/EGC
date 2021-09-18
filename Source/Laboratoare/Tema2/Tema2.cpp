#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

struct Platform {
	float x;
	float y;
	float z;
	glm::vec3 color;
};
struct Platform platforms[3][4];

float platformLength = 2.5f;
float platformWidth = 1.2f;
float platformHeight = .3f;

// culori folosite
glm::vec3 redC = glm::normalize(glm::vec3(255, 0, 0));
glm::vec3 greenC = glm::normalize(glm::vec3(0, 255, 0));
glm::vec3 blueC = glm::normalize(glm::vec3(0, 0, 255));
glm::vec3 cyanC = glm::normalize(glm::vec3(0, 255, 255));
glm::vec3 yellowC = glm::normalize(glm::vec3(255, 255, 0));
glm::vec3 orangeC = glm::normalize(glm::vec3(255, 140, 0));
glm::vec3 purpleC = glm::normalize(glm::vec3(128, 0, 128));

float totalFuel = 3000;
float penaltyFuel = 1000;

float ballX = 0;
float ballY = 2;
float ballZ = 1;
bool movingDown = true;
bool movingUp = false;
float ballSpeed = 2.2f;
float fuel = totalFuel;

float timeForOrange = 5;

clock_t startTime; // pentru masurarea timpului
clock_t currentTime;
bool orangeEffect = false;
float lastSpeed;

TextRenderer* textRenderer;

glm::vec3 colors[5] = {orangeC, yellowC, redC, greenC, blueC};
glm::vec3 getRandomColor();

void Tema2::Init()
{
	srand(time(NULL));
	glm::ivec2 resolution = window->GetResolution();
	textRenderer = new TextRenderer(resolution.x, resolution.y);
	textRenderer->Load("Source/TextRenderer/Fonts/Arial.ttf", 30);

	float line = -2;

	// creez platformele
	for (int i = 0; i < 3; i++) {
		glm::vec3 color;
		float distanceBetweenPlatforms = -5;
		float extraDistance = -((float) (rand() % 200 + 50)) / 100;

		for (int j = 0; j < 4; j++) {
			platforms[i][j].x = line;
			platforms[i][j].y = 0;
			platforms[i][j].z = distanceBetweenPlatforms + extraDistance;
			platforms[i][j].color = getRandomColor();
			distanceBetweenPlatforms -= (platformLength + 2.5);
			extraDistance = -((float)(rand() % 200 + 50)) / 100;
		}
		line += 2;
	}

	// prima platforma trb sa fie albastra si pozitionata corect
	platforms[1][0].z = -6.f;
	platforms[1][0].color = blueC;

	camera = new Laborator::CameraTema();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("Platform");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// pentru shadere
	{
		Shader* shader = new Shader("Tema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::Update(float deltaTimeSeconds)
{
	// afisez viteza
	textRenderer->RenderText("Nivel " + std::to_string((int)(ballSpeed * 2.5 - 5)), 50, 10, 1, greenC);

	// verific daca s-a terminat combustibilul
	if (fuel <= 0) {
		exit(0);
	}

	// afisez combustibilul
	fuel--;
	float scaleX = 5 * fuel / totalFuel;
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(9.f - (5 - scaleX) / 2, 4.5f, -10.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, 0.5f, 0.0001f));
		RenderMesh(meshes["Platform"], shaders["Tema2"], modelMatrix, greenC);
	}
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(9.f, 4.5f, -10.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 0.5f, 0.0001f));
		RenderMesh(meshes["Platform"], shaders["Tema2"], modelMatrix, blueC);
	}

	// afisez si verific daca s-a consumat timpul pentru efectul platformei portocalii
	if (orangeEffect) {
		textRenderer->RenderText("Timp ramas:" + std::to_string(((int)(timeForOrange - (float)
			(currentTime - startTime) / CLOCKS_PER_SEC))), 50, 600, 1, orangeC);
		currentTime = clock();
		if ((float)(currentTime - startTime) / CLOCKS_PER_SEC >= timeForOrange) {
			orangeEffect = false;
			ballSpeed = lastSpeed;
		}
	}

	// verific daca bila aterizeaza pe o platforma --- coliziuni
	bool ballDown = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			struct Platform* platform = &platforms[i][j];
			glm::vec3 color;
			// iau punctul de pe platforma cel mai apropiat de centrul bilei
			float platformX = std::max(platform->x - platformWidth / 2, std::min(ballX, platform->x + platformWidth / 2));
			float platformY = std::max(platform->y - platformHeight / 2, std::min(ballY, platform->y + platformHeight / 2));
			float platformZ = std::max(platform->z - platformLength / 2, std::min(ballZ, platform->z + platformLength / 2));
			float distance = sqrt((platformX - ballX) * (platformX - ballX)
				+ (platformY - ballY) * (platformY - ballY)
				+ (platformZ - ballZ) * (platformZ - ballZ));

			// a doua conditie e ca coliziunea sa se faca doar cand bila este pe placa sau deasupra ei, nu dedesubt
			if (distance < 0.3f && ballY >= 0.15f) {

				// verific culoarea platformei
				if (platform->color == redC) {
					exit(0);
				} else if (platform->color == orangeC && movingDown) {
					lastSpeed = ballSpeed;
					ballSpeed = 3.8f;
					orangeEffect = true;
					startTime = clock();
				} else if (platform->color == greenC && movingDown) {
					if (fuel > totalFuel - penaltyFuel) {
						fuel = totalFuel;
					} else {
						fuel += penaltyFuel;
					}
				} else if (platform->color == yellowC && movingDown) {
					if (fuel < penaltyFuel) {
						exit(0);
					}
					else {
						fuel -= penaltyFuel;
					}
				}

				movingDown = false;
				color = purpleC; // schimb culoarea platformei in mov
				ballDown = true;
			} else {
				color = platform->color;
			}

			// misc platformele
			platform->z += ballSpeed * deltaTimeSeconds;
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(platform->x, platform->y, platform->z));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(platformWidth, platformHeight, platformLength));
				RenderMesh(meshes["Platform"], shaders["Tema2"], modelMatrix, color);
			}
			// refolosesc platformele, resetandu-le pozitia cand trec de o anumita coordonata
			if (platform->z >= 5) {
				float distanceBetweenPlatforms = -4 * (platformLength + 2.5) + 5;
				float extraDistance = -((float)(rand() % 200 + 50)) / 100;
				platform->color = getRandomColor();
				platform->z = distanceBetweenPlatforms + extraDistance;
			}
		}
	}

	// misc bila
	if (movingUp) {
		if (ballY >= 1.8) {
			movingUp = false;
			movingDown = true;
		}
		else {
			ballY += 8 * deltaTimeSeconds * (2.1f - ballY) * (ballSpeed / 2);
		}
	} else if (movingDown) {
		ballY -= 1 * deltaTimeSeconds * (2.1f - ballY) * (ballSpeed / 2);
	}

	// verific daca bila a cazut de pe platforma
	if (ballY < -3) {
		exit(0);
	}
	// afisez bila
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(ballX, ballY, ballZ));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f));
		RenderMesh(meshes["sphere"], shaders["Tema2"], modelMatrix, cyanC);
	}
	if (!ballDown && !movingUp) {
		movingDown = true;
	}
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->program)
		return;
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	auto locObject = glGetUniformLocation(shader->program, "color");
	glUniform3fv(locObject, 1, glm::value_ptr(color));

	mesh->Render();
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_W && !orangeEffect) {
		if (ballSpeed < 3.8f) {
			ballSpeed += 0.4f;
		}
	}
	if (key == GLFW_KEY_S && !orangeEffect) {
		if (ballSpeed > 2.2f) {
			ballSpeed -= 0.4f;
		}
	}
	if (key == GLFW_KEY_A && (movingUp || movingDown)) {
		if (ballX >= 0) {
			ballX -= 2;
		}
	}
	if (key == GLFW_KEY_D && (movingUp || movingDown)) {
		if (ballX <= 0) {
			ballX += 2;
		}
	}
	if (key == GLFW_KEY_SPACE) {
		if (!movingDown && !movingUp) {
			movingUp = true;
		}
	}
}

// genereaza o culoare random, majoritatea sunt albastre
glm::vec3 getRandomColor() {
	int randomIndex = rand() % 11;
	if (randomIndex > 4) {
		randomIndex = 4;
	}
	glm::vec3 color = colors[randomIndex];
	return color;
}

void Tema2::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color) {}
void Tema2::OnKeyRelease(int key, int mods) {}
void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {}
void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}
void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}
void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
void Tema2::OnWindowResize(int width, int height) {}
void Tema2::OnInputUpdate(float deltaTime, int mods) {}
void Tema2::FrameEnd() {}
Tema2::Tema2() {}
Tema2::~Tema2() {}