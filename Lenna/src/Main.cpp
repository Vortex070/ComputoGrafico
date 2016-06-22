
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Application.h"

Application app;

//Se tiene que llamar despues de inicializar la ventana y el OpenGL, pero antes del main loop
void setup()
{
	app.setup();
}

//Se ejecuta siempre que se necesite actualizar la imagen
void display()
{
	app.display();
}

//Se ejecuta cuando la ventana cambia de tamaño. Parámetros en pixeles.
//(ojo: En otros programas se debe ejecutar glViewport)
void reshape(int w, int h)
{
	app.reshape(w, h);
}

void keyboard(GLFWwindow * window, int key, int scanCode, int action, int mods) {
	app.keyboard(key, scanCode, action, mods);
}

void _update_fps_counter(GLFWwindow* window) {
	static double previous_seconds = glfwGetTime();//funcion para obtener tiempo
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf_s(tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

static void  cursor_pos_callback(GLFWwindow * window, double Xpos, double Ypos) {
	//if (window == app.window)
		app.cursor_position(Xpos, Ypos);
}


int main(int argc, char *argv[])
{
	Application app;

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Plane", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);//ocupar esta ventana para openGL

	glewExperimental = GL_TRUE; 
	glewInit();
	app.setup();

	// get version info 
	const GLubyte* renderer = glGetString (GL_RENDERER); 
	const GLubyte* version = glGetString (GL_VERSION); 
	printf (" Renderer: %s\ n", renderer); 
	printf (" OpenGL version supported %s\ n", version); 
	
	// tell GL to only draw onto a pixel if the shape is closer to the viewer 
	//glEnable (GL_DEPTH_TEST); // enable depth-testing 	
	//glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer" 

	glViewport(0, 0, (GLsizei)1024, (GLsizei)768);


	glfwSetCursorPosCallback(window, cursor_pos_callback);

	while (!glfwWindowShouldClose(window))
	{
		//_update_fps_counter(window);
		/* update other events like input handling */
		glfwPollEvents();
		//glfwSetCursorPosCallback(window, cursor_pos_callback);

		app.update();

		/* put the stuff we've been drawing onto the display */
		app.display();
		
		glfwSwapBuffers(window);
	}
	
	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;

}
