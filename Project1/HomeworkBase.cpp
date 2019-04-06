#include "HomeworkBase.h"
HomeworkBase::HomeworkBase(const string & vertexShaderFile, const string & fragmentShaderFile)
{
	ShaderProgram shaderProgramIns(vertexShaderFile, fragmentShaderFile);
	shaderProgram = shaderProgramIns.getShaderProgram();
}

HomeworkBase::~HomeworkBase()
{
}