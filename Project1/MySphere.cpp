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
	float theta = 0; // ��
	float phi = 0; // ��
	// ����ÿ������
	for (int i = 0; i < SLICEX; i++) {
		for (int j = 0; j < SLICEY; j++) {
			theta = thetaStep * i;
			phi = phiStep * j;
			// ��������
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