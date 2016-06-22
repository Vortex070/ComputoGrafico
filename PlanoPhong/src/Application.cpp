#include "Application.h"
#include <iostream>
#include <vector>
#include "Plane.h"
#include "GLFW/glfw3.h"
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ShaderFuncs.h"
//#include "SOIL.h"

float width = 1024.0f;
float height = 768.0f;

std::string strVertexShader, 
			strFragmentShader;


Application::Application() :oPlane(), 
							fAngle(0.0),
							eye(0.0f, 0.0f, 100.0f),
							target(0.0f, 0.0f, 0.0f),
							up(0.0f, 1.0f, 0.0f),
							light(50.0f,50.0f,50.0f)
							
{}

Application::~Application()
{}

void Application::setup()
{
	oPlane.createPlane(40);
	std::string sVertex = loadTextFile("shaders/gouraudPlane.v");
	std::string sFragment = loadTextFile("shaders/passThru.f");

	InitializeProgram(oPlane.shader[0], sVertex, sFragment);
	InitializeProgram(oPlane.shader[1], sVertex, sFragment);

	oPlane.uTransform[0] = glGetUniformLocation(oPlane.shader[0], "mTransform");
	oPlane.uTime[0] = glGetUniformLocation(oPlane.shader[0], "fTime");
	oPlane.uEye[0] = glGetUniformLocation(oPlane.shader[0], "vEye");
	oPlane.uLightPos[0] = glGetUniformLocation(oPlane.shader[0], "myLightPosition");

	oPlane.uTransform[1] = glGetUniformLocation(oPlane.shader[1], "mTransform");
	oPlane.uTime[1] = glGetUniformLocation(oPlane.shader[1], "fTime");
	oPlane.uEye[1] = glGetUniformLocation(oPlane.shader[1], "vEye");
	oPlane.uLightPos[1] = glGetUniformLocation(oPlane.shader[1], "myLightPosition");


	glGenVertexArrays(1, &oPlane.vao);
	glBindVertexArray(oPlane.vao);
	glGenBuffers(1, &oPlane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, oPlane.vbo);

	glBufferData(GL_ARRAY_BUFFER,oPlane.getVertexSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, oPlane.getVertexSizeInBytes(), oPlane.plane);
	

	oPlane.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//glEnable(GL_CULL_FACE);

	
}


void Application::display()
{
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	glPolygonMode(GL_FRONT, GL_FILL);


	//Seleccionamos los shaders a usar
	glUseProgram(oPlane.shader[0]);

	//activamos el vertex array object y dibujamos
	//glBindVertexArray(oPlane.vao);

	//glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f));
	//position = glm::translate(position, glm::vec3(-10.0f, -10.0f, -0.9f));

	glm::mat4 mTransform = glm::rotate(glm::mat4(1.0), oPlane.aRotations.x, glm::vec3(1.0, 0.0, 0.0));
	mTransform = glm::rotate(mTransform, oPlane.aRotations.y, glm::vec3(0.0, 1.0, 0.0));
	mTransform = glm::rotate(mTransform, oPlane.aRotations.z, glm::vec3(0.0, 0.0, 1.0));

	glm::vec4 newLightPos = mTransform *glm::vec4(light, 1.0f);

	glm::mat4 transform = camera;
	transform = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 200.0f) * transform * mTransform;

	glUniformMatrix4fv(oPlane.uTransform[0], 1, GL_FALSE, glm::value_ptr(transform));
	glUniform3fv(oPlane.uEye[0], 1, glm::value_ptr(eye));
	glUniform3fv(oPlane.uLightPos[0], 1, glm::value_ptr(light));
	glUniform1f(oPlane.uTime[0], fTime);

	glDrawArrays(GL_TRIANGLES, 0, oPlane.getNumVertex());
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::update()
{
	fTime = glfwGetTime();
	//fTime = 0;

	oPlane.rotation = glm::rotate(glm::mat4(1.0f), fTime, glm::vec3(0.0f, 1.0f, 0.0f));
	camera = glm::lookAt(eye, target, glm::vec3(0.0f, 1.0f, 0.0f));
	//std::cout << fAngle << std::endl;
}

void Application::cursor_position(double Xpos, double Ypos) {
	oPlane.aRotations.y = -((Xpos - width / 2.0)/100.0);
	oPlane.aRotations.x = ((Ypos + height / 2.0)/100.0);
}

void Application::keyboard(int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		exit(0);
}