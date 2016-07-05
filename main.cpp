#include <stdio.h>
#include <stdlib.h>

#include <GLFW\glfw3.h>

#include "PerspectiveCamera.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Rotator.h"
#include "Image.h"
#include "Renderer.h"

int main(int argc, char **argv){


	uint Width = 100;
	uint Height = 100;
	PerspectiveCamera* Cam = new PerspectiveCamera(Vector3(), Rotator(), Width, Height, 90);
	Renderer R = Renderer(Width, Height);

	R.Render(Cam);

	delete Cam;


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}



	glfwTerminate();
	return 0;


}