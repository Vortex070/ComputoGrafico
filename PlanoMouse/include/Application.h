#pragma once

#include <iostream>
#include "Object3D.h"
#include "Plane.h"
#include "glm/matrix.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Application {
public:
	Application();
	~Application();

	void setup();
	void display();
	void reshape(int w, int h);
	void update();
	void keyboard(int key, int scanCode, int action, int mods);
	void avanza();
	void rotIzquierda();
	void Application::cursor_position(double Xpos, double Ypos);

private:
	Object3D cube;
	
	Plane oPlane;
	
	float fAngle;
	float fTime;

	glm::mat4 camera, mTra;
	glm::vec3 eyeDirection;
	glm::vec3 eye,
			  target,
				up,
				light;
};

