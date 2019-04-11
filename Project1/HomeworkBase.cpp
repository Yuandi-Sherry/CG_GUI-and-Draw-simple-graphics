#include "HomeworkBase.h"
HomeworkBase::HomeworkBase(const string & vertexShaderFile, const string & fragmentShaderFile)
{
	Shader shaders(vertexShaderFile, fragmentShaderFile);
	shaderProgramIns.setShaders(shaders.getVertexShader(), shaders.getFragmentShader());
	shaderProgram = shaderProgramIns.getShaderProgram();
	cout << "base " << shaderProgram << endl;
}


HomeworkBase::~HomeworkBase()
{

}