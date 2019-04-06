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
	unsigned int VBO, VAO, EBO; // 顶点数组对象 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	
	// 位置、颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	unsigned int indices[] = {
		// 0, 1, 2, // 第一个三角形
		3, 4, 5, // 第二个三角形
		6, 7, 8, // 第三个三角形
		9, 10, 11, // 第四个三角形
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
	// 这里的 缓冲类型为GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(400, 200, 400, 400); // 注意视口要加载use之前
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