#include "Homework8.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
using namespace std;
extern int windowWidth;
extern int windowHeight;
extern float lastX;
extern float lastY;
void Homework8::displayController() {
	// deal with animation
	currentT += speed;
	calculateAssLines();
	drawAssLines();
	if (currentT > 1) {
		currentT = 0;
	}
	// basic
	displayControlPoints();
	drawLine(controlPointsVertices);
	displayBeizerCurve();
}
void Homework8::displayControlPoints() {
	if (controlPointsVertices.size() != 0) {
		drawPoints(controlPointsVertices);
	}
	
}
void Homework8::drawPoints(const vector<float> & pointsVec) {
	if (pointsVec.size() != 0) {
		initVBOVAO(cpVAO, cpVBO, 1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pointsVec.size(), &pointsVec[0], GL_STATIC_DRAW);
		glViewport(0, 0, 1200, 1200);
		glUseProgram(shaderProgram);

		glBindVertexArray(cpVAO);
		glPointSize(radius);
		glDrawArrays(GL_POINTS, 0, pointsVec.size() / 6);
		glBindVertexArray(0);

		glDeleteVertexArrays(1, &cpVAO);
		glDeleteBuffers(1, &cpVBO);
	}
	
}
void Homework8::calculateBeizer() {
	beizerCurveVertices.clear();
	if (n == 0)
		return;
	for (double t = 0; t <= 1; t += deltaT) {
		float x = 0, y = 0;
		for (int i = 0; i <= n; i++) {
			x += controlPointsVertices[6 * i] * bernstain(t, i);
			y += controlPointsVertices[6 * i + 1] * bernstain(t, i);
		}
		vector<float> tmp = {
			x, y, 0, 1, 1, 1
		};
		beizerCurveVertices.insert(beizerCurveVertices.end(), tmp.begin(), tmp.end());
	}
}

void Homework8::displayBeizerCurve() {
	if (beizerCurveVertices.size() > 6) {
		initVBOVAO(bzVAO, bzVBO, 1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * beizerCurveVertices.size(), &beizerCurveVertices[0], GL_STATIC_DRAW);
		glViewport(0, 0, 1200, 1200);
		glUseProgram(shaderProgram);
		glBindVertexArray(bzVAO);
		glPointSize(1.0f);
		glDrawArrays(GL_POINTS, 0, beizerCurveVertices.size() / 6);
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &bzVAO);
		glDeleteBuffers(1, &bzVBO);
	}
}
Homework8::~Homework8() {

}
void Homework8::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework8")) {
		//ImGui::MenuItem("Basic", NULL, &basic);
		ImGui::EndMenu();
	}
}
void Homework8::imGuiSetting() {
}
Homework8::Homework8() {

}
void Homework8::init(const string & vertexShaderFile, const string & fragmentShaderFile) {
	HomeworkBase::init(vertexShaderFile, fragmentShaderFile);
	shaderProgram = HomeworkBase::shaderProgram;
	initVars();
}

void Homework8::mouseCallback(GLFWwindow* window, double xoffset, double yoffset) {
	// ��ʱ��õ�ǰ����
	currentX = xoffset;
	currentY = yoffset;
}

void Homework8::mouseButtonCallBack(int button, int action) {
	// get the position being clicked
	lockX = ((float)currentX - windowWidth / 2) / (windowWidth / 2);
	lockY = (-1)*((float)currentY - windowHeight / 2) / (windowHeight / 2);
	// add 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {	
		addControlPoints();
	}
	// delete
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		deleteControlPoints();
	}
	n = controlPointsVertices.size() / 6 - 1;
	calculateBeizer();
}

void Homework8::addControlPoints() {
	vector<float> tmp = {
		(float)lockX, (float)lockY, 0, 1, 1, 1
	};
	controlPointsVertices.insert(controlPointsVertices.end(), tmp.begin(), tmp.end());
}

void Homework8::deleteControlPoints() {
	for (int i = 0; i < controlPointsVertices.size(); ) {
		if (abs(controlPointsVertices[i] - lockX) < radius / windowWidth * 2 && abs(controlPointsVertices[i + 1] - lockY) < radius / windowHeight * 2) {
			for (int j = 0; j < 6; j++) {
				controlPointsVertices.erase(controlPointsVertices.begin() + i);
			}
		}
		else {
			i += 6;
		}
	}
}

void Homework8::initVars() {
	vector<float> tmp = {
		0, 0, 0, 1, 1, 1,
		0, 1, 0, 1, 0, 1,
		0.5, 0, 0, 1, 1, 1
	};
	//controlPointsVertices.assign(tmp.begin(), tmp.end());
	controlPointsVertices.clear();
	radius = 10.0f;
	deltaT = 0.001f;
	n = 0;
	currentT = 0.0f;
	speed = 0.001f;
	calculateBeizer();
}

double Homework8::bernstain(double t, int i) {
	double ans = combineNumber(i);
	ans *= pow(t, i) * pow(1 - t, n - i);
	return ans;
}

int Homework8::combineNumber(int i) {
	int ans = 1;
	for (int j = 0; j < i; j++) {
		ans *= (n - j);
	}
	for (int j = 0; j < i; j++) {
		ans /= (i - j);
	}
	return ans;
}
void Homework8::initVBOVAO(GLuint & VAO, GLuint & VBO, int id) {
	glGenBuffers(id, &VBO);
	glGenVertexArrays(id, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// λ�á���ɫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Homework8::drawLine(const vector<float> & lineVec) {
	if (lineVec.size() > 6) {
		for (int i = 0; i < lineVec.size() / 6 - 1; i++) {
			initVBOVAO(lineVAO, lineVBO, 1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, &lineVec[i * 6], GL_STATIC_DRAW);
			glViewport(0, 0, 1200, 1200);
			glUseProgram(shaderProgram);
			glBindVertexArray(lineVAO);
			glDrawArrays(GL_LINE_STRIP, 0, 2); // ע�����ﲻ��GL_LINE
			glBindVertexArray(0);
			glDeleteVertexArrays(1, &lineVAO);
			glDeleteBuffers(1, &lineVBO);
		}
	}
}

void Homework8::drawAssLines() {
	int count = 0;
	for (int i = controlPointsVertices.size() / 6 - 1; i > 1; i--) {
		vector<float> tmp(lines.begin() + count * 6, lines.begin() + count*6 + i*6);
		count += i;
		drawLine(tmp);
	}
	drawPoints(lines);
	
}

void Homework8::calculateAssLines() {
	lines.clear();
	if (controlPointsVertices.size() > 6) {
		// 处理第一层
		for (int i = 0; i < controlPointsVertices.size() / 6 - 1; i++) {
			float x = (1 - currentT) * controlPointsVertices[i * 6] + currentT * controlPointsVertices[(i + 1) * 6];
			float y = (1 - currentT) * controlPointsVertices[i * 6 + 1] + currentT * controlPointsVertices[(i + 1) * 6 + 1];
			vector<float> tmp = {
				x,y,0,1,1,1
			};
			lines.insert(lines.end(), tmp.begin(), tmp.end());
		}
		recursive(lines.size() / 6);
	}
}
/**
 * count为上一层线段的数目 + 1, 即控制点的数目
 */
void Homework8::recursive(int count) {
	int tmpSize = lines.size();
	if (count < 2) {
		return;
	}
	for (int i = tmpSize / 6 - count; i < tmpSize / 6 - 1; i++) {
		float x = (1 - currentT) * lines[i * 6] + currentT * lines[(i + 1) * 6];
		float y = (1 - currentT) * lines[i * 6 + 1] + currentT * lines[(i + 1) * 6 + 1];
		vector<float> tmp = {
			x,y,0,1,1,1
		};
		lines.insert(lines.end(), tmp.begin(), tmp.end());
	}
	recursive(count - 1);
}