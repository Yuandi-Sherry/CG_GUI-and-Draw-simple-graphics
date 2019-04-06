#pragma once
#include "ShaderProgram.h"
class HomeworkBase
{
public:
	HomeworkBase(const string & vsFile, const string & fsFile);
	~HomeworkBase();
protected:
	int shaderProgram;
};

