#include "HomeworkBase.h"
HomeworkBase::HomeworkBase(const string & vertexShaderFile, const string & fragmentShaderFile)
{
	Shader shaders(vertexShaderFile, fragmentShaderFile);
	ShaderProgram shaderProgramIns(shaders.getVertexShader(), shaders.getFragmentShader());
	shaderProgram = shaderProgramIns.getShaderProgram();
}

HomeworkBase::~HomeworkBase()
{
}