#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp> // glm::value_ptr
#include <glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Utils.h"
using namespace std;

#define numVAOs 1
#define numVBOs 4

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

void setupVertices(void)
{

	float topPyr[21] = {
		-1.0f, 1.0f,0.0f,	1.0f,0.0f,0.0f,1.0f,
		1.0f, 1.0f,0.0f,	1.0f,0.0f,0.0f,1.0f,
		0.0f, 0.0f,0.0f,	1.0f,0.0f,0.0f,1.0f
	};

	float leftPyr[21] = {
		-1.0f,1.0f,0.0f,	0.0f,1.0f,0.0f,1.0f,
		-1.0f,-1.0f,0.0f,	0.0f,1.0f,0.0f,1.0f,
		0.0f,0.0f,0.0f,		0.0f,1.0f,0.0f,1.0f
	};

	float bottomPyr[21] = {
		-1.0f,-1.0f,0.0f,	0.0f,0.0f,1.0f,1.0f,
		1.0f,-1.0f,0.0f,	0.0f,0.0f,1.0f,1.0f,
		0.0f,0.0f,0.0f,		0.0f,0.0f,1.0f,1.0f
	};

	float rightPyr[21] = {
		1.0f,1.0f,0.0f,		1.0f,0.5f,0.0f,1.0f,
		1.0f,-1.0f,0.0f,	1.0f,0.5f,0.0f,1.0f,
		0.0f,0.0f,0.0f,		1.0f,0.5f,0.0f,1.0f
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(topPyr), topPyr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftPyr), leftPyr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bottomPyr), bottomPyr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rightPyr), rightPyr, GL_STATIC_DRAW);

}

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");

	setupVertices();
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);
	glBindVertexArray(vao[0]);




	for (int i = 0; i < numVBOs; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glm::mat4 vMatrix = glm::mat4(1.0f);
		GLuint mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
		vMatrix *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(vMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glRotatef(15.0f, 0.0f, 0.0f, 0.0f);
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 4 - program 1d", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}