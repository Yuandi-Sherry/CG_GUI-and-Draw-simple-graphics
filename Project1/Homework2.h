#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace std;
class Homework2
{
public:
	Homework2(const int & shaderProgram);
	~Homework2();
	void displayPoint();
	void displayLine();
	void displayRec();
	void displayTriangle();
	void displaySeveralTriangle();

	bool homework2;
	bool basic;
	bool triangle;
	bool bonus;
	bool point;
	bool line;
	bool rectangle;
	bool severalTri;
	ImVec4 triangleColor = ImVec4(-1.0f, -1.0f, -1.0f, 1.00f);
	void displayController();
	void imGuiSetting();
	void imGuiMenuSetting();
private:
	int shaderProgram;
	void initBool();
	
	bool dirty; // �޸���������ɫ
};

