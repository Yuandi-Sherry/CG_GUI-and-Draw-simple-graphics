#include "Homework6.h"

extern int windowWidth;
extern int windowHeight;
extern float lastX;
extern float lastY;
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
	setCubeVAOVBO();
	setLightSourceVAO();
	Shader shader1("light_shader.vs", "light_shader.fs");
	lightShader.setShaders(shader1.getVertexShader(), shader1.getFragmentShader());
	Shader shader2("light_shader.vs", "light_source.fs");
	lightSource.setShaders(shader2.getVertexShader(), shader2.getFragmentShader());
}
Homework6::~Homework6()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void Homework6::initVars() {
	homework6 = true;
	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
}
void Homework6::displayController() {
	if (homework6) {
		showLightedCube();
		showLightSource();
	}
}

void Homework6::showLightSource() {
	lightSource.useProgram();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = view = camera.getViewMatrix();
	// lightSource.setMat4("projection", projection);
	glUniformMatrix4fv(glGetUniformLocation(lightSource.getShaderProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);
	// lightSource.setMat("view", view);
	glUniformMatrix4fv(glGetUniformLocation(lightSource.getShaderProgram(), "view"), 1, GL_FALSE, &view[0][0]);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	// lightSource.setMat4("Model", model);
	glUniformMatrix4fv(glGetUniformLocation(lightSource.getShaderProgram(), "model"), 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Homework6::showLightedCube (){

	lightShader.useProgram();
	glUniform3f(glGetUniformLocation(lightShader.getShaderProgram(), "lightPosition"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(lightShader.getShaderProgram(), "objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation(lightShader.getShaderProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	
}
void Homework6::setLightSourceVAO() {
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Homework6::setCubeVAOVBO() {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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

void Homework6::processInput(GLFWwindow * window) {
	// º¸≈Ã ‰»Î
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processKeyboard(FORWARD, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processKeyboard(BACKWARD, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.processKeyboard(LEFT, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processKeyboard(RIGHT, 0.1);
	}
}


void Homework6::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	camera.processMouseMovement(xoffset, yoffset);

}