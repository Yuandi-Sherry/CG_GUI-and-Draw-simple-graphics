#pragma once
#ifndef _shader_h_
#define _shader_h_
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
using namespace std;
class ShaderProgram
{
public:
	ShaderProgram(const string & vsFile, const string & fsFile);
	~ShaderProgram();
	unsigned int getShaderProgram() {
		return shaderProgram;
	}
	
private:
	unsigned int shaderProgram;
	void compileShader(unsigned int & shader, const string & filename, const int & shaderType);
	bool readFile(const string & fileName, string & content);

	void checkCompile(const int & shader, const int & checkType);
};
#endif // !ShaderProgram
