
#include "Application.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include "GLFW/glfw3.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "ShaderFuncs.h"
#include "Plane.h"
#include "SOIL.h"

float width = 1024.0f;
float height = 768.0f;

std::string sVertex, sFragment;

Application::Application() : plane1Texture(),
							 eye(0.0f, 50.0f, 100.0f),
							 target(0.0f, 0.0f, 0.0f),
							 up(0.0f, 1.0f, 0.0f)
{}

Application::~Application() 
{}

void Application::loadShaders()
{
	sVertex = loadTextFile("Shaders/passThru.v");
	sFragment = loadTextFile("Shaders/passThru.f");
}

void Application::setup()
{
	plane1Texture.texture_id = initTexture("Lenna.png");
	plane1Texture.texture_id2 = initTexture("Lenna2.png");
	//initTexture("Princess_bubblegum_character.png");

	plane1Texture.createPlane(100);
	loadShaders();
	InitializeProgram(plane1Texture.shader[0], sVertex, sFragment);
	InitializeProgram(plane1Texture.shader[1], sVertex, sFragment);

	/*plane1Texture.uTransform[0] = glGetUniformLocation(plane1Texture.shader[0], "mTransform");
	plane1Texture.uTime[0] = glGetUniformLocation(plane1Texture.shader[0], "fTime");
	plane1Texture.uTexture[0] = glGetUniformLocation(plane1Texture.shader[0], "theTexture");*/

	plane1Texture.uTransform[1] = glGetUniformLocation(plane1Texture.shader[1], "mTransform");
	plane1Texture.uTime[1] = glGetUniformLocation(plane1Texture.shader[1], "fTime");
	plane1Texture.uTexture[1] = glGetUniformLocation(plane1Texture.shader[1], "theTexture");
	plane1Texture.uTexture[1] = glGetUniformLocation(plane1Texture.shader[1], "theOtherTexture");

	glGenVertexArrays(1, &plane1Texture.vao);
	glBindVertexArray(plane1Texture.vao);
	glGenBuffers(1, &plane1Texture.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane1Texture.vbo);
	
	glBufferData(GL_ARRAY_BUFFER, plane1Texture.getVertexSizeInBytes() + plane1Texture.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, plane1Texture.getVertexSizeInBytes(), plane1Texture.plane);
	glBufferSubData(GL_ARRAY_BUFFER, plane1Texture.getVertexSizeInBytes(), plane1Texture.getTextureCoordsSizeInBytes(), plane1Texture.textureCoords);

	plane1Texture.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)plane1Texture.getVertexSizeInBytes());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
}

GLuint Application::initTexture(const char* img)
{
	int img_width, img_height;
	int channels;
	GLuint Tid;
	//OJO: SOIL	entrega la imagen de cabeza
	unsigned char* Img = SOIL_load_image(img, &img_width, &img_height, &channels, 0);
	//unsigned char* img2 = SOIL_load_image("Pepe.png", &img_width, &img_height, &channels, 1);

	glGenTextures(1, &Tid);
	glBindTexture(GL_TEXTURE_2D, Tid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, Img);
	
	//glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img_width, img_height, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(Img);
	

	// Mipmap generation is now included in OpenGL 3 and above
	glGenerateMipmap(GL_TEXTURE_2D);

	// Trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bilinear filtering
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Sin promediar
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	return Tid;
}



void Application::display()
{
	//Borramos el buffer de color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(plane1Texture.vao);
	glUseProgram(plane1Texture.shader[0]);
	
	//aplicar transformaciones
	//rotaciones
	glm::mat4 mTransform = glm::rotate(glm::mat4(1.0), plane1Texture.aRotations.x, glm::vec3(1.0, 0.0, 0.0));
	mTransform = glm::rotate(mTransform, plane1Texture.aRotations.y, glm::vec3(0.0, 1.0, 0.0));
	mTransform = glm::rotate(mTransform, plane1Texture.aRotations.z, glm::vec3(0.0, 0.0, 1.0));

	//proyecciones y cámara
	//glm::mat4 mProjection = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, -10.0f, 10.0f);//Ortogonal
	glm::mat4 mProjection = glm::perspective(45.0f, width / height, 0.1f, 200.0f);//Perspectiva
	glm::mat4 mCamera = glm::lookAt(eye, target, up);

	//acumulación de matrices
	glm::mat4 finalMatrix = glm::mat4(1.0);
	//finalMatrix = mProjection * mTransform;
	finalMatrix = mProjection * mCamera * mTransform;
	//finalMatrix = mProjection * mCamera;

	//Seleccionamos los shaders a usar
	//glUseProgram(plane1.shader[0]);
	glUniformMatrix4fv(plane1Texture.uTransform[0], 1, GL_FALSE, glm::value_ptr(finalMatrix));
	glUniform1f(plane1Texture.uTime[0], fTime);
	
	
	//textura 0
	glUniform1i(plane1Texture.uTexture[0], 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, plane1Texture.texture_id);

	glUniform1i(plane1Texture.uTexture[1], 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, plane1Texture.texture_id2);
	
	//activamos el vertex array object y dibujamos
	glDrawArrays(GL_TRIANGLES, 0, plane1Texture.getNumVertex());


}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::keyboard(int key, int scanCode, int action, int mods) {
	
}

void Application::cursor_position(double Xpos, double Ypos) {
	plane1Texture.aRotations.y = -((Xpos - width / 2.0f) / 100.0f);
	plane1Texture.aRotations.x = ((Ypos + height / 2.0f) / 100.0f);
}


void Application::update()
{
	fTime = glfwGetTime() * 2;
	//plane1.aRotations.x = glfwGetTime();
	//plane1.aRotations.y = glfwGetTime();
	//plane1.aRotations.z = glfwGetTime();
}