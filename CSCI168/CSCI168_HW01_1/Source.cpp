#include <stdio.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

void Display(GLFWwindow* window, double currentTime) {
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
	if (!glfwInit()) {
		printf("GLFW failed to init\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - Program 1", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit != GLEW_OK) {
		printf("glew failed to init\n");
		return -1;
	}

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window)) {
		Display(window,glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}