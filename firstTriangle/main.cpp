#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h> // for abs and sin

#include "RGB.h"

#define WINDOWWIDTH 1280
#define WINDOWHEIGHT 720

// press escape to close application (can also click X in top right)
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// resizes viewport when window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// fullscreen:
	// GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "First Triangle", glfwGetPrimaryMonitor(), nullptr); 
	GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "First Triangle", nullptr, nullptr);
	if (!window)
	{
		std::cout << "faild to create window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}

	const char* vertexShaderSource
	{	"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 vertexColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0f);\n"
		"	vertexColor = aColor;\n"
		"}\0"
	};

	const char* fragmentShaderSource
	{	"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 vertexColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vertexColor, 1.0f);\n"
		"}\0"
	};

	unsigned vertexShader, fragmentShader, shaderProgram;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// COLORS
	RGB bgColor{ 5, 5, 11 };

	const RGB blColor{ 110, 114, 254 };
	const RGB brColor{ 65, 0, 124 };
	const RGB tmColor{ 95, 26, 144 };

	GLfloat vertices[]
	{
	//	positions				colors
		-0.35f, -0.35f, 0.00f,		blColor.r, blColor.g, blColor.b, // bottom left
		 0.35f, -0.35f, 0.00f,		brColor.r, brColor.g, brColor.b, // bottom right
		 0.00f,  0.70f, 0.00f,		tmColor.r, tmColor.g, tmColor.b  // top middle
	};

	unsigned triangleVAO, triangleVBO;
	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &triangleVBO);

	glBindVertexArray(triangleVAO);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0x00);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(0, 0, WINDOWWIDTH, WINDOWHEIGHT);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		bgColor.b = (::abs(6 * ::sin(glfwGetTime() / 2)) + 11.0f) / 255.0f;
		glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(triangleVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &triangleVAO);
	glDeleteBuffers(1, &triangleVBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}