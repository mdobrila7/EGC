#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	float translateX, translateY, translate, translateShurikken, translateShurikken2, translateShurikken3, translateShurikken4;
	float translateBalloon, translateArrowX, translateArrowY;
	float scaleX, scaleY;
	float angularStep;
	float VelX, VelY;
	int width;
	int height;
	float mouseX;
	float mouseY;
	float radians;
	float bow_posY = 360;
	float bow_posX = 50;
	float bow_radius = 100;
	float arrow_posX = 50;
	float angularStep2 = 0;
	float arrow_posY = 360;
	float arrow_posY_relative = 360;
	float arrow_width = 110;
	float nr_shuri = 3;
	float shuriken_posX[3];
	float shuriken_posY[3];
	float angularStep4 = 0;
	int bow_pos_up_corner = 0;
	float arrow_height = 1;
	float peak_length = 15;
	float angularStep3 = 0;
	float angularStepBow = 0;
	float angularStepArrow = 0;
	float arrowSpeed = 0;
	bool Release = false;
	bool Hold = false;
};
