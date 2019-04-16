#pragma once
#ifndef _HOMEWORK_5_
#define _HOMEWORK_5_
#include "HomeworkBase.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Homework5 : public HomeworkBase
{
public:
	Homework5(const string & vertexShaderFile, const string & fragmentShaderFile);
	// basic1 投影
	void drawCube(); // basic1:画一个立方体
	// basic2 视角变换
	// basic3 菜单栏
	
	void displayController();
	~Homework5();
	void imGuiSetting();
	void imGuiMenuSetting();
	void initVars();
	void processInput();
private:
	bool homework5;
	// basic part
	// the length of the cube
	float length = 2.0f;
	// initial position in world coordinate
	float x;
	float y;
	float z;

	float cubeVertices[216] = {
		// red z = -2
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		// purple z = 2
		-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		// yellow z = 
		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		// blue z = 
		 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 // green
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		// qing
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 1.0f
	};
	int shaderProgram;
	// basic 1
	bool coordinate_transform;
	// 选择透视
	bool per;
	// 透视投影
	float pro_frov;
	float pro_near;
	float pro_far;
	// 正交投影
	float ort_left;
	float ort_right;
	float ort_bottom;
	float ort_top;
	float ort_near;
	float ort_far;
	// basic 2
	bool viewChanging;
	// camera
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
};



#endif // !_HOMEWORK_5_
