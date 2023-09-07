#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 1080;
const unsigned int height = 720;


//meshes go here
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

GLfloat vertices2[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-2.5f, -0.0001f,  2.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-2.5f, -0.0001f, -2.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 2.5f, -0.0001f, -2.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 2.5f, -0.0001f,  2.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f
};

GLuint indices2[] =
{
	0, 1, 2,
	0, 2, 3
};
// end of meshes area
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(width, height, "CrazyGl - Main", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");
	Shader shaderProgram2("default.vert", "default1.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	//test

	VAO VAO2;
	VAO2.Bind();

	VBO VBO2(vertices2, sizeof(vertices2));
	EBO EBO2(indices2, sizeof(indices2));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();
	//test
	
	//texture
	Texture defaultimg("./noimage.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	defaultimg.texUnit(shaderProgram, "tex0", 0);

	Texture defaultgrass("./grass1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	defaultgrass.texUnit(shaderProgram2, "tex1", 1);
	
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();
		
		camera.Inputs(window);
		camera.Matrix(45.0f, 0.01f, 100.0f, shaderProgram, "camMatrix");
		
		//lighting area
		


		//lighting area
		defaultimg.Bind();
		VAO1.Bind();
		glad_glActiveTexture(0);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		defaultimg.Unbind();
		
		shaderProgram2.Activate();
		camera.Matrix(45.0f, 0.01f, 100.0f, shaderProgram2, "camMatrix");
		
		defaultgrass.Bind();
		
		VAO2.Bind();
		glad_glActiveTexture(1);

		glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(int), GL_UNSIGNED_INT, 0);
		defaultgrass.Unbind();
		glfwSwapBuffers(window);


		glfwPollEvents();
	}


	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	defaultgrass.Delete();
	defaultimg.Delete();
	shaderProgram.Delete();
	shaderProgram2.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}