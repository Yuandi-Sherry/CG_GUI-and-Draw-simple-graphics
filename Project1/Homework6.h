#pragma once
#ifndef HOMEWORK_6_
#include "Camera.h"
#include "HomeworkBase.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Homework6 : public HomeworkBase
{
public:
	Homework6();
	Homework6(const string & vertexShaderFile, const string & fragmentShaderFile);
	~Homework6();
	void init(const string & vertexShaderFile, const string & fragmentShaderFile);
	void displayController();
	void imGuiSetting();
	void imGuiMenuSetting();
	
private:
	// control
	bool homework6;

	// cube
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
	// init position
	float x, y, z;
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	// light source
	unsigned int lightVAO;
	glm::vec3 lightPos; // ��Դ�ڳ���������ռ������е�λ��

	// int
	void initVars();
	
	void setCubeVAOVBO();
	void setLightSourceVAO();
	
	// show
	ShaderProgram lightSource;
	unsigned int lightSourceID;
	ShaderProgram lightShader;
	unsigned int lightShaderID;
	void showLightSource();
	void showLightShader();
	void showCube();
	Camera camera;


};

#endif // !HOMEWORK_6_
