#pragma once
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;
class MySphere
{
public:
	MySphere(const float & radius);
	~MySphere();
	vector<float> getVBOarr();
private:
	vector<float> VBOarr;
};
