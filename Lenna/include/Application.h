#pragma once

#include <iostream>
#include "Object3D.h"
#include "Plane.h"
//glm
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Application {

public:
	Application();
	~Application();

	void setup();
	void display();
	void reshape(int w, int h);
	void update();
	void keyboard(int key, int scanCode, int action, int mods);
	void cursor_position(double Xpos, double Ypos);
	GLuint initTexture(const char* img);

private:	
	void loadShaders();
	Plane plane1Texture;
	//Object3D cube;
	GLint uTransform;
	float fTime;
	glm::mat4 camera;
	glm::vec3 eye, target, up;
};

