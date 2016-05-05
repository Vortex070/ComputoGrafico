
#include "Application.h"
#include <iostream>
#include <vector>

#include "GLFW/glfw3.h"
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>



//#include "GL/freeglut.h"

#include "ShaderFuncs.h"

GLfloat vertexPositions[] = {
	//cuadrado//
	/*0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,

	-0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, 0.75f, 0.0f, 1.0f,*/
	
	//cubo//

	//Blue
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,

	1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,

	//Green
	1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,

	//Red
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,


	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	//Orange
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,

	//White
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,

	//Yellow
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,

	-1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f
};


GLfloat vertexColors[] = {
	//cuadrado//
	/*1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,

	0.0, 0.0, 1.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,*/
	//cubo//

	//Blue
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	//Green
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	//Roja
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	//Orange
	1.0f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.5f, 0.0f, 1.0f,

	//White
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	//Yellow
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f
};

std::string strVertexShader, 
			strFragmentShader;


Application::Application() :fAngle(0.0),
							eye(1.5f, 1.5f, -1.5f),
							target(0.0f, 0.0f, 0.0f)
{}

Application::~Application()
{}

void Application::loadShaders() 
{
	strVertexShader = loadTextFile("shaders/vertexShader1.vs");
	strFragmentShader = loadTextFile("shaders/fragmentShader1.fs");
}

void Application::setup()
{
	loadShaders();
	InitializeProgram(cube.shader, strVertexShader, strFragmentShader);
	uTransform = glGetUniformLocation(cube.shader, "transform");

	cube.numVertex = 36;
	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);
	glGenBuffers(1, &cube.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0/*offset*/, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
}


void Application::display()
{
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Seleccionamos los shaders a usar
	glUseProgram(cube.shader);

	//activamos el vertex array object y dibujamos
	glBindVertexArray(cube.vao);

	for (int i = 0; i < 10;i++)
	{ 	
		for (int j = 0; j < 10;j++)
		{
			glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f*i));
			position = glm::translate(position, glm::vec3(-10.0f, -10.0f, -0.9f));

			glm::mat4 transform = camera * position/* cube.rotation*/;
			transform = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f) * transform;
			glUniformMatrix4fv(uTransform, 1, GL_FALSE, glm::value_ptr(transform));
			glDrawArrays(GL_TRIANGLES, 0, cube.numVertex);
		}
	}
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::update()
{
	fAngle = glfwGetTime();

	cube.rotation = glm::rotate(glm::mat4(1.0f), fAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	camera = glm::lookAt(eye, target, glm::vec3(0.0f, 1.0f, 0.0f));


	//std::cout << fAngle << std::endl;
}

void Application::keyboard(int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		exit(0);

	if (action == GLFW_RELEASE)
		return;

	switch (key)
	{
	case GLFW_KEY_W: avanza(); break;
	case GLFW_KEY_A: rotIzquierda(); break;
	//case GLFW_KEY_S: retrocede(); break;
	//case GLFW_KEY_D: rotDerecha(); breaK;
	}

}

void Application::avanza()
{
	glm::vec3 direction = target - eye;
	direction = normalize(direction);
	eye = eye + direction;
	target = target + direction;
}
void Application::rotIzquierda()
{

}