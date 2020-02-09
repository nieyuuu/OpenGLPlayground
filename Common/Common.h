#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "../stb_image/stb_image.h"
#include "Camera.h"

int WindowWidth = 1000;
int WindowHeight = 800;

float LastX = WindowWidth / 2.0f;
float LastY = WindowHeight / 2.0f;

bool FirstMouse = true;

float DeltaTime = 0.0f;
float LastFrameTime = 0.0f;

GLFWwindow* sWindow = nullptr;
Camera		sCamera(glm::vec3(0.0f, 0.0f, 3.0f));

void framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight)
{
	glViewport(0, 0, vWidth, vHeight);
	WindowWidth = vWidth;
	WindowHeight = vHeight;
}

void mousePosCallback(GLFWwindow* vWindow, double xPos, double yPos)
{
	if (FirstMouse)
	{
		LastX = (float)xPos;
		LastY = (float)yPos;
		FirstMouse = false;
	}

	float xOffset = (float)xPos - LastX;
	float yOffset = LastY - (float)yPos; // reversed since y-coordinates go from bottom to top

	LastX = (float)xPos;
	LastY = (float)yPos;

	sCamera.ProcessMouseMovement(xOffset, yOffset);
}

void srcollCallback(GLFWwindow* vWindow, double xOffset, double yOffset)
{
	sCamera.ProcessMouseScroll((float)yOffset);
}

void processInput(GLFWwindow* vWindow)
{
	if (glfwGetKey(vWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(vWindow, true);

	if (glfwGetKey(vWindow, GLFW_KEY_W) == GLFW_PRESS)
		sCamera.ProcessKeyboard(FORWARD, DeltaTime);
	if (glfwGetKey(vWindow, GLFW_KEY_S) == GLFW_PRESS)
		sCamera.ProcessKeyboard(BACKWARD, DeltaTime);
	if (glfwGetKey(vWindow, GLFW_KEY_A) == GLFW_PRESS)
		sCamera.ProcessKeyboard(LEFT, DeltaTime);
	if (glfwGetKey(vWindow, GLFW_KEY_D) == GLFW_PRESS)
		sCamera.ProcessKeyboard(RIGHT, DeltaTime);
	if (glfwGetKey(vWindow, GLFW_KEY_Q) == GLFW_PRESS)
		sCamera.ProcessKeyboard(UP, DeltaTime);
	if (glfwGetKey(vWindow, GLFW_KEY_E) == GLFW_PRESS)
		sCamera.ProcessKeyboard(DOWN, DeltaTime);
}

void updateTime()
{
	float CurrentFrameTime = (float)glfwGetTime();
	DeltaTime = CurrentFrameTime - LastFrameTime;
	LastFrameTime = CurrentFrameTime;
}

bool init(bool vResizable = true)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, vResizable);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	sWindow = glfwCreateWindow(WindowWidth, WindowHeight, "OpenGL", nullptr, nullptr);
	if (sWindow == nullptr)
	{
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(sWindow);

	glfwSetFramebufferSizeCallback(sWindow, framebufferSizeCallback);
	glfwSetCursorPosCallback(sWindow, mousePosCallback);
	glfwSetScrollCallback(sWindow, srcollCallback);

	glfwSetInputMode(sWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init glew" << std::endl;
		glfwDestroyWindow(sWindow);
		glfwTerminate();
		return false;
	}

	return true;
}

void destroy()
{
	glfwDestroyWindow(sWindow);
	glfwTerminate();
}

unsigned int generateTexture2D(const std::string& vTextureFile, bool vFlipVertically = true, bool vMipmap = true)
{
	unsigned int Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int Width, Height, Channel;
	stbi_set_flip_vertically_on_load(vFlipVertically);
	unsigned char* Pixel = stbi_load(vTextureFile.c_str(), &Width, &Height, &Channel, 0);

	if (Pixel)
	{
		unsigned int Format = GL_RGB;
		if (Channel == 4) Format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Pixel);
		if (vMipmap)
			glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(Pixel);
	}
	else
	{
		std::cout << "Failed to create texture: " << vTextureFile.c_str() << std::endl;
		glDeleteTextures(1, &Texture);
		stbi_image_free(Pixel);
		glBindTexture(GL_TEXTURE_2D, 0);
		return 0;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return Texture;
}