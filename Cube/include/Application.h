#pragma once

#include <iostream>
#include "Object3D.h"

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

private:	
	Object3D cube;

	void loadShaders();
	GLuint uTransform;
	float fAngle;

	glm::mat4 camera;
	glm::vec3 eye,
			  target;
};

