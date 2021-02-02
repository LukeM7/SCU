#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define numVAOs 1

GLuint renderingProgram, vao[numVAOs];

GLuint createShaderProgram() {
	const char* vShaderCode =
		"#version 430	\n"
		"void main(void)\n"
		"{ if(gl_VertexID == 0) gl_Position = vec4(0.25f,-0.25f,0.0f,1.0f);"
		"else if (gl_VertexID == 1) gl_Position = vec4(-0.25f,-0.25f,0.0f,1.0f);"
		"else gl_Position = vec4(0.0f,0.50f,0.0f,1.0f);}";

	const char* fShaderCode =
		"#version 430	\n"
		"out vec4 color;\n"
		"void main(void)\n"
		"{ color = vec4(0.0f,0.0f,1.0f,1.0f); }";

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vShaderCode, NULL);
	glShaderSource(fShader, 1, &fShaderCode, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	return vfProgram;
}

void Init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void Display(GLFWwindow* window, double currentTime) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);


}

int main() {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(600, 600, "HW 01 - 1", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	Init(window);

	while (!glfwWindowShouldClose(window)) {
		Display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}