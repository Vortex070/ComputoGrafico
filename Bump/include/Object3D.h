#pragma once

#include <iostream>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "glm/matrix.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"




class Object3D{
public:
	GLuint	vao, //Vertex Array Object
			vbo; //Vertex Buffer Object

	int numVertex; //numero de vertices para este objeto

	GLuint shader[2]; //referencia a los shaders
	glm::mat4 rotation;
	//Object3D();

};

