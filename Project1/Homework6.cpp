#include "Homework6.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
extern int windowWidth;
extern int windowHeight;
Homework6::Homework6(const string & vertexShaderFile, const string & fragmentShaderFile) {
	init(vertexShaderFile, fragmentShaderFile);
	
}
Homework6::Homework6() {

}
void Homework6::init(const string & vertexShaderFile, const string & fragmentShaderFile) {
	HomeworkBase::init(vertexShaderFile, fragmentShaderFile);
	shaderProgram = HomeworkBase::shaderProgram;
	initVars();
	camera.setCamera(glm::vec3(0.0f, 0.0f, 20.0f));
}
Homework6::~Homework6()
{
}
void Homework6::initVars() {
	homework6 = true;
}
void Homework6::displayController() {
	if (homework6) {
		showCube();
	}
}

void Homework6::showCube() {
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
	//glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	// 透视投影
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	view = camera.getViewMatrix();
	
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	// 绘制
	shaderProgramIns.useProgram();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void Homework6::imGuiSetting() {

}
void Homework6::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework6")) {
		if (ImGui::BeginMenu("Basic")) {
			/*ImGui::MenuItem("Coordinate Transform", NULL, &coordinate_transform);
			ImGui::MenuItem("View Changeing", NULL, &viewChanging);
			ImGui::MenuItem("FPS", NULL, &FPS);*/
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Bounus")) {
			/*ImGui::MenuItem("Coordinate Transform", NULL, &coordinate_transform);
			ImGui::MenuItem("View Changeing", NULL, &viewChanging);
			ImGui::MenuItem("FPS", NULL, &FPS);*/
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}