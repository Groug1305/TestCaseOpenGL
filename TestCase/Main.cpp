#define GLM_ENABLE_EXPERIMENTAL

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS         /   TexCoord  //
  //  x     z      y     /					     /	 x     y   //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//0-3 pyramid bottom
	-0.5f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.0f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	-0.25f,0.4f,  0.25f,    0.92f, 0.86f, 0.76f,	0.5f, 1.0f,	//4 pyramid top
  //							cube						   //
	 0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//5-8 cube front
	 0.5f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.4f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.1f, 0.4f, -0.1f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 0.1f, 0.4f, -0.1f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//9-12 cube top
	 0.5f, 0.4f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.4f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.1f, 0.4f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//13-16 cube bottom
	 0.5f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.1f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 0.1f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//17-20 cube back
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.4f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.1f, 0.4f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//21-24 cube left
	 0.5f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.4f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.5f, 0.4f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,

	 0.1f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//25-28 cube right
	 0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.1f, 0.4f, -0.1f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.1f, 0.4f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,
	//						triangle bottom						//
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	//29-32 pyramid bottom (for texture)
	-0.5f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 0.0f,  0.0f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
	 0.0f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,
};

// Indices for vertices order
GLuint indices[] =
{	//			   pyramid					//
	//0, 1, 2,	//pyramid bottom triangle 1
	//0, 2, 3,	//pyramid bottom triangle 2
	29, 30, 31, //pyramid bottom (for texture)
	29, 31, 32,

	0, 1, 4,	//pyramid side 1
	1, 2, 4,	//pyramid side 2
	2, 3, 4,	//pyramid side 3
	3, 0, 4,	//pyramid side 4
	//				cube					//
	5, 6, 7,	//cube front
	5, 7, 8,

	9, 10, 11,	//cube top
	9, 11, 12,
	
	13, 14, 15,	//cube bottom
	13, 15, 16,
	
	17, 18, 19,	//cube back
	17, 19, 20,

	21, 22, 23,	//cube left
	21, 23, 24,

	25, 26, 27,	//cube right
	25, 27, 28
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "TestCase"
	GLFWwindow* window = glfwCreateWindow(width, height, "TestCase", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Setting texture
	Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}