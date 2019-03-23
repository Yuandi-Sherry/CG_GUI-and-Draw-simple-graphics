#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cmath>
class Homework3
{
public:
	Homework3(const float vertices[6], const int & shaderProgram);
	Homework3(const float & centerX, const float & centerY, const float & radius, const int & shaderProgram);
	Homework3(const int & shaderProgram);
	~Homework3() {

	}
	void drawTriangle();
	void drawCircle();
	void setTriangle(const float & p1x = -0.5, const float & p1y = 0.5, const float & p2x = -0.0, const float & p2y = 1.0, const float & p3x = 0.5, const float & p3y = -0.5);
	void setCircle(const float & centerX = 0, const float & centerY = 0, const float & radius = 0.5);
	void fillTriangle();
	void displayController();
	void imGuiSetting();
	void imGuiMenuSetting();

	// options
	bool triangleFrame;
	bool circleFrame;
	bool filledTri;
	// input Vars
	int centerInt[2];
	int radiusInt;
	// tri
	int point1[2];
	int point2[2];
	int point3[2];
private:
	// const
	float color[3] = { 1.0f, 0, 0 };
	int shaderProgram;
	// triangle
	float triangleVertex[6];
	float top, bottom, left, right;
	// circle
	float center[2];
	float radius;
	// basic Methods
	void drawPoint(const float location[3], const float color[3], const int & VAO, const int &VBO);
	void drawLine(const float startPoint[2], const float endPoint[2], const int & VAO, const int &VBO);
	// draw circle
	float judgePosReltoCircle(const float & x, const float & y);
	void draw8points(const float & x, const float & y);
	// fill Tri
	bool isInTri(const float & x, const float & y, const float * edge1, const float * edge2, const float * edge3);
	void initVars();
	void initBound();
	
};

