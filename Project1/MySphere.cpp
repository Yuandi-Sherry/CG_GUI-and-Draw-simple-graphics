#include "MySphere.h"
#include <vector>
using namespace std;
GLint SLICEY = 60;	
GLint SLICEX = 60; 
double PI = 3.14159265;
MySphere::MySphere(const float & radius)
{
	/*float phiStep = PI / SLICEY;
	float thetaStep = 2 * PI / SLICEX;
	float theta = 0; // θ
	float phi = 0; // φ
	// 计算每个坐标
	for (int i = 0; i < SLICEX; i++) {
		for (int j = 0; j < SLICEY; j++) {
			theta = thetaStep * i;
			phi = phiStep * j;
			// 参数方程
			float x = radius * sin(phi) * cos(theta);
			float y = radius * sin(phi) * sin(theta);
			float z = radius * cons(phi);
		}
	}*/


}

MySphere::~MySphere()
{
}

vector<float> MySphere::getVBOarr() {
	return VBOarr;
}