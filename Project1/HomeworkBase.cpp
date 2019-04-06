#include "HomeworkBase.h"
HomeworkBase::HomeworkBase(const string & vertexShaderFile, const string & fragmentShaderFile)
{
	Shader shaders(vertexShaderFile, fragmentShaderFile);
	vertexShader = shaders.getVertexShader();
	fragmentShader = shaders.getFragmentShader();
	shaderProgramIns.setShaders(vertexShader, fragmentShader);
	shaderProgram = shaderProgramIns.getShaderProgram();
}


HomeworkBase::~HomeworkBase()
{
}