#include <iostream>
#include "Homework4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
Homework4::Homework4(const string & vertexShaderFile, const string & fragmentShaderFile) : HomeworkBase(vertexShaderFile, fragmentShaderFile) {
	
	Shader vertexShader();
	// test
	cout << "default constructor for homework4" << endl;
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	cout << vec.x << vec.y << vec.z << std::endl;

}
Homework4::~Homework4()
{

}

void Homework4::drawCube() {
	//	cout << "displayCube" << endl;
	unsigned int VBO, VAO, EBO; // ����������� 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	
	// λ�á���ɫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	unsigned int indices[] = {
		// 0, 1, 2, // ��һ��������
		3, 4, 5, // �ڶ���������
		6, 7, 8, // ������������
		9, 10, 11, // ���ĸ�������
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};
	//cout << "size of indices" << sizeof(indices) / sizeof(int) << endl;
	// ����� ��������ΪGL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(400, 200, 400, 400); // ע���ӿ�Ҫ����use֮ǰ
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void Homework4::translation() {

}
void Homework4::rotation() {

}
void Homework4::scaling() {

}

void Homework4::displayController() {
	drawCube();
}