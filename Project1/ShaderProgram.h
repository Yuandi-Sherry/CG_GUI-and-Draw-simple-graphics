#pragma once
#ifndef _shader_h_
#define _shader_h_
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include "Shader.h"
using namespace std;
class ShaderProgram
{
public:
	ShaderProgram(const int & vShader, const int & fShader);
	~ShaderProgram();
	void checkCompile(const int & shaderProgram);
	unsigned int getShaderProgram() {
		return shaderProgram;
	}
	
private:
	unsigned int shaderProgram;

};
#endif // !ShaderProgram
