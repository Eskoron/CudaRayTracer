
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "PerspectiveCamera.h"
#include "CudaDefines.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include "Vector3.h"
#include "Rotator.h"
#include "Image.h"
#include "Renderer.h"
#include <GLFW\glfw3.h>


int main()
{


	uint Width = 100;
	uint Height = 100;
	PerspectiveCamera* Cam = new PerspectiveCamera(Vector3(), Rotator(), Width, Height, 45);
	Renderer R = Renderer(Width, Height);





	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Width, Height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glClearColor(1, 0, 0, 1);

	Color* pixels = (Color*)malloc(Width*Height*sizeof(Color));

	glEnable(GL_TEXTURE_2D);
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	/* Loop until the user closes the window */

	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	int Amount_Spheres = 3;

	Sphere* spheres;
	spheres = (Sphere*)malloc(Amount_Spheres * sizeof(Sphere));

	spheres[0].Position = Vector3(10, 0, 0);
	spheres[0].Radius = 5;

	spheres[1].Position = Vector3(0, 10, 0);
	spheres[1].Radius = 5;

	spheres[2].Position = Vector3(0, 0, 10);
	spheres[2].Radius = 5;

	while (!glfwWindowShouldClose(window))
	{
		float r = (float)((double)rand() / (RAND_MAX)) + 1;
		for (uint i = 0; i < Width*Height; i++){

			pixels[i].R = (uchar)255;
			pixels[i].G = (uchar)255;
			pixels[i].B = (uchar)255;
			pixels[i].A = (uchar)255;
		}



		R.Render(Cam, spheres, Amount_Spheres, pixels);

		cudaDeviceSynchronize();


		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Render here */
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		glViewport(0, 0, windowWidth, windowHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, 0, 1);
		glMatrixMode(GL_MODELVIEW);





		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		//glColor3f(0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1, -1);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1, -1);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1, 1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1, 1);
		glEnd();

		//glDrawPixels(Width,Height,GL_RGBA8,GL_UNSIGNED_BYTE,pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	free(pixels);
	delete Cam;

	glfwTerminate();
	return 0;

}
