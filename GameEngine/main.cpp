#define GLEW_STATIC

#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "soil/soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Sprite.h"
#include "Animotion.h"
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <ctime>

//vertex shader
const GLchar* vertexSource =
"#version 150 core\n"
"in vec4 position;"
"in vec4 color;"
"in vec2 texcoord;"
"uniform mat4 mvp_matrix;"
"out vec4 Color;"
"out vec2 Texcoord;"
"void main() {"
"   Color = color;"
"   Texcoord = texcoord;"
"   gl_Position = mvp_matrix * position;"
//"   gl_Position = position;"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec4 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"void main() {"
"   outColor = texture(tex, Texcoord) * Color;"
"}";

static bool printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
		return false;
	}
	else
	{
		printf("Info log was empty\n");
	}
	return true;
}

int main()
{
	glfwInit();

	int screenWidth = 1080;
	int screenHeight = 800;

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, ":3", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit() != GLEW_OK;

	//compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// get debugging info for shaders
	printShaderInfoLog(vertexShader);
	printShaderInfoLog(fragmentShader);

	// compile shaderprogram
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//Nodes
	Graph graph;
	GraphNode * node1 = new GraphNode(1);
	GraphNode * node2 = new GraphNode(2);
	GraphNode * node3 = new GraphNode(3);

	Edge edge;

	graph.AddNode(node1);
	graph.AddNode(node2);
	graph.AddNode(node3);

	edge.a_Start = node1;
	edge.a_End = node3;
	edge.a_Cost = 2;
	
	Edge edge2;
	edge2.a_Start = node1;
	edge2.a_End = node2;
	edge2.a_Cost = 3;

	node1->a_Edge.push_back(edge);
	node1->a_Edge.push_back(edge2);

	node1->PrintNeigh();

	graph.sprite = new Sprite("gridtiles.png", 1, 1, 800, 800);
	graph.sprite->uiShaderProg = shaderProgram;

	std::cout << "Success? " << graph.searchDFS(node1, node3) << std::endl;
	std::cout << "And? " << graph.searchDijkstra(node1, node2) << std::endl;
	std::cout << "Pls. " << graph.searchAStar(node1, node2, 0) << std::endl;
	std::cout << "K, So? " << graph.searchThetaStar(node1, node2, 0) << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		graph.sprite->Draw();

		glfwPollEvents();
		resetDeltaTime();
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	glfwTerminate();

	return 0;
} 