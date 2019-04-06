#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const int & vertexShader, const int & fragmentShader)
{
	shaderProgram = glCreateProgram();
	// 链接
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkCompile(shaderProgram);
	// 激活程序对象
	glUseProgram(shaderProgram);
}

ShaderProgram::~ShaderProgram()
{
}





void ShaderProgram::checkCompile(const int & shader) {
	int success;
	char info[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		cout << "COMPILE ERROR: " << endl;
		glGetProgramInfoLog(shader, 512, NULL, info);
		cout << info << endl;
	}
}