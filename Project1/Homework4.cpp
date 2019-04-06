#include <iostream>
#include "Homework4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

using namespace std;
extern int windowWidth;
extern int windowHeight;
Homework4::Homework4(const string & vertexShaderFile, const string & fragmentShaderFile) : HomeworkBase(vertexShaderFile, fragmentShaderFile) {
	shaderProgram = HomeworkBase::shaderProgram;
	initVars();
}
Homework4::~Homework4()
{

}

void Homework4::drawCube() {
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	shaderProgramIns.useProgram();
	// 计算矩阵
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(translateX, translateY, translateZ));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	if(rotation)
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	// 绘制
	shaderProgramIns.useProgram();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void Homework4::translate() {

}
void Homework4::rotate() {

}
void Homework4::scale() {

}

void Homework4::displayController() {
	if(homework4)
		drawCube();
}

void Homework4::imGuiSetting() {
	// 变换的是view
	if (translation) {
		ImGui::Text("Translation");
		ImGui::SliderFloat("X", &translateX, -50, 50);
		ImGui::SliderFloat("Y", &translateY, -50, 50);
		ImGui::SliderFloat("Z", &translateZ, -50, 50);
	}
	// 变换的是model
	if (scaling) {
		ImGui::Text("Scaling");
		ImGui::SliderFloat("Scalar", &scalar, 0.001, 10);
		for (int i = 0; i < 36; i++) {
			for (int j = 0; j < 3; j++) {
				cubeVertices[i * 6 + j] = (double)length * scalar * cubeVertices[i * 6 + j] / abs(cubeVertices[i * 6 + j]);
			}
		}
	}
	
}
void Homework4::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework4"))
	{
		if (ImGui::BeginMenu("Basic"))
		{
			
			ImGui::MenuItem("Translation", NULL, &translation);
			ImGui::MenuItem("Rotation", NULL, &rotation);
			ImGui::MenuItem("Scaling", NULL, &scaling);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Bonus"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void Homework4::initVars() {
	homework4 = true;
	translation = false;
	translateX = 0.0f;
	translateY = 0.0f;
	translateZ = -20.0f;
	rotation = false;
	rotateX = false;
	rotateY = false;
	rotateZ = false;
	scaling = false;
	scalar = 1.0f;
}