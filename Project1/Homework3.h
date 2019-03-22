#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
class Homework3
{
public:
	Homework3(const float vertices[6], const int & shaderProgram);
	Homework3(const float center[2], const float & radius, const int & shaderProgram);
	Homework3(const int & shaderProgram);
	~Homework3() {

	}
	void drawTriangle();
	void drawCircle();
	void setTriangle(const float vertices[6]);
	void setCircle(const float center[2], const float & radius);
	bool homework3;
	bool triangleFrame;
	bool circleFrame;
private:
	float triangleVertex[6];
	int shaderProgram;
	float center[2];
	float radius;
	void drawPoint(const float location[3], const float color[3]);
	void drawLine(const float startPoint[2], const float endPoint[2]);
	float color[3] = { 1.0f, 0, 0 };
	float judgePosReltoCircle(const float & x, const float & y);
	void draw8points(const float & x, const float & y);
	void initBools();
	
};

