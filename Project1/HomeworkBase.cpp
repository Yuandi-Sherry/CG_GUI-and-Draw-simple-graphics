#include "HomeworkBase.h"
HomeworkBase::HomeworkBase(const string & vertexShaderFile, const string & fragmentShaderFile)
{
	Shader shaders(vertexShaderFile, fragmentShaderFile);
	shaderProgramIns.setShaders(shaders.getVertexShader(), shaders.getFragmentShader());
	shaderProgram = shaderProgramIns.getShaderProgram();
}


HomeworkBase::~HomeworkBase()
{

}

HomeworkBase::HomeworkBase() {

}
void HomeworkBase::init(const string & vsFile, const string & fsFile) {
	Shader shaders(vsFile, fsFile);
	shaderProgramIns.setShaders(shaders.getVertexShader(), shaders.getFragmentShader());
	shaderProgram = shaderProgramIns.getShaderProgram();
}