#pragma once
#ifndef _Homework_4_
#define _Homework_4_
#include "HomeworkBase.h"
class Homework4 : public HomeworkBase
{
public:
	Homework4(const string & vertexShaderFile, const string & fragmentShaderFile);
	void drawCube(); // basic1:画一个立方体
	void translate();
	void rotate();
	void scale();
	void displayController();
	~Homework4();
	void imGuiSetting();
	void imGuiMenuSetting();
	void initVars();

private:
	bool homework4;
	float length = 2.0f;
	float cubeVertices [216] = {
		// red
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		 2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		 2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		 2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 0.0f, 0.0f,
		// purple
		-2.0f, -2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		 2.0f, -2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		-2.0f,  2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		-2.0f, -2.0f,  2.0f,  1.0f, 0.0f, 1.0f,
		// qing
		-2.0f,  2.0f,  2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f,  2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f, -2.0f,  2.0f,  1.0f, 1.0f, 0.0f,
		-2.0f,  2.0f,  2.0f,  1.0f, 1.0f, 0.0f,
		// blue
		 2.0f,  2.0f,  2.0f,  0.0f, 0.0f, 1.0f,
		 2.0f,  2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		 2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		 2.0f, -2.0f, -2.0f,  0.0f, 0.0f, 1.0f,
		 2.0f, -2.0f,  2.0f,  0.0f, 0.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  0.0f, 0.0f, 1.0f,
		 // green
		-2.0f, -2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		 2.0f, -2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		 2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		 2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		-2.0f, -2.0f,  2.0f,  0.0f, 1.0f, 0.0f,
		-2.0f, -2.0f, -2.0f,  0.0f, 1.0f, 0.0f,
		// yellow
		-2.0f,  2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		 2.0f,  2.0f, -2.0f,  0.0f, 1.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  0.0f, 1.0f, 1.0f,
		 2.0f,  2.0f,  2.0f,  0.0f, 1.0f, 1.0f,
		-2.0f,  2.0f,  2.0f,  0.0f, 1.0f, 1.0f,
		-2.0f,  2.0f, -2.0f,  0.0f, 1.0f, 1.0f
	};
	int shaderProgram;
	bool translation;
	float translateX;
	float translateY;
	float translateZ;
	bool rotation;
	bool rotateX;
	bool rotateY;
	bool rotateZ;
	bool scaling;
	float scalar;
};



#endif // !_homework_4_
