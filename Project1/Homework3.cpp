#include "Homework3.h"
extern int windowWidth;
extern int windowHeight;
Homework3::Homework3(const float vertices[6], const int & shaderProgram)
{
	initBools();
	this->shaderProgram = shaderProgram;
	setTriangle(vertices);
	for (int i = 0; i < 2; i++) {
		center[i] = 0;
	}
	radius = 0.5;
}

Homework3::Homework3(const float center[2], const float & radius, const int & shaderProgram)
{
	initBools();
	this->shaderProgram = shaderProgram;
	setCircle(center, radius);
	triangleVertex[0] = -0.5;
	triangleVertex[1] = 0.5;
	triangleVertex[2] = 0.0;
	triangleVertex[3] = 1.0;
	triangleVertex[4] = 0.5;
	triangleVertex[5] = -0.5;
}

Homework3::Homework3(const int & shaderProgram)
{
	initBools();
	this->shaderProgram = shaderProgram;
	for (int i = 0; i < 2; i++) {
		this->center[i] = 0;
	}
	this->radius = 1;
	triangleVertex[0] = -0.5;
	triangleVertex[1] = 0.5;
	triangleVertex[2] = 0.0;
	triangleVertex[3] = 1.0;
	triangleVertex[4] = 0.5;
	triangleVertex[5] = -0.5;
}

void Homework3::setTriangle(const float vertices[6]) {
	for (int i = 0; i < 6; i++) {
		triangleVertex[i] = vertices[i];
	}
}
void Homework3::setCircle(const float center[2], const float & radius) {
	for (int i = 0; i < 2; i++) {
		this->center[i] = center[i];
	}
	this->radius = radius;
}

void Homework3::drawPoint(const float location[3], const float color[3], const int & VAO, const int & VBO) {
	float pointVertex[6];
	for (int i = 0; i < 3; i++) {
		pointVertex[i] = location[i];
	}
	for (int i = 0; i < 3; i++) {
		pointVertex[i + 3] = color[i];
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertex), pointVertex, GL_STATIC_DRAW);
	glViewport(0, 0, windowWidth, windowHeight);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
}

void Homework3::drawLine(const float startPoint[2], const float endPoint[2], const int & VAO, const int &VBO) {
	float deltaX = abs(endPoint[0] - startPoint[0]);
	float deltaY = abs(endPoint[1] - startPoint[1]);
	float stepX = (endPoint[0] - startPoint[0]) / deltaX * (float)2 / windowWidth;
	float stepY = (endPoint[1] - startPoint[1]) / deltaY * (float)2 / windowHeight;
	float y_i = startPoint[1];
	float x_i = startPoint[0];
	

	// 判断斜率与45°的大小
	if (abs(deltaY / deltaX) < 1) {
		float p_i = 2 * deltaY - deltaX;
		// cout << "stepX" << stepX << endl << "stepY" << stepY << endl;
		while (abs(x_i - startPoint[0]) < abs(endPoint[0] - startPoint[0])) {
			float loc[3] = { x_i, y_i, 0 };
			drawPoint(loc, color, VAO, VBO);
			if (p_i <= 0) {
				p_i = p_i + 2 * deltaY;
			}
			else {
				p_i = p_i + 2 * deltaY - 2 * deltaX;
				y_i = y_i + stepY;
			}
			x_i = x_i + stepX;
		}
	}
	else {
		float p_i = 2 * deltaY - deltaX;
		while (abs(y_i - startPoint[1]) < abs(endPoint[1] - startPoint[1])) {
			float loc[3] = { x_i, y_i , 0 };
			drawPoint(loc, color, VAO, VBO);
			if (p_i <= 0) {
				p_i = p_i + 2 * deltaX;
			}
			else {
				p_i = p_i + 2 * deltaX - 2 * deltaY;
				x_i = x_i + stepX;
			}
			y_i = y_i + stepY;
		}
	}
}

void Homework3::drawTriangle() {
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 位置、颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	float point1[2] = { triangleVertex[0], triangleVertex[1] };
	float point2[2] = { triangleVertex[2], triangleVertex[3] };
	float point3[2] = { triangleVertex[4], triangleVertex[5] };
	drawLine(point1, point2, VAO, VBO);
	drawLine(point1, point3, VAO, VBO);
	drawLine(point2, point3, VAO, VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework3::drawCircle() {
	float d_i = 5.0 / 4 - radius;
	float stepX = (float)2 / windowWidth;
	float stepY = (float)2 / windowHeight;
	float y_i = center[1] + radius;
	float x_i = center[0];

	while (x_i < center[0] + sqrt(2) * radius/2 + stepX ) {
		float loc[3] = { x_i, y_i, 0 };
		draw8points(x_i, y_i);
		if (d_i < 0) {
			d_i = judgePosReltoCircle(x_i, y_i);
		}
		else {
			d_i = judgePosReltoCircle(x_i, y_i);
			y_i = y_i - stepY;
		}
		x_i = x_i + stepX;
	}
}

float Homework3::judgePosReltoCircle(const float & x, const float & y) {
	return pow(x, 2) + pow(y, 2) - pow(radius, 2);
}

void Homework3::draw8points(const float & x, const float & y) {
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 位置、颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	float deltaX = x - center[0];
	float deltaY = y - center[1];
	float xArray[8] = {center[0] + x, center[0] + x, center[0] - x, center[0] - x, center[0] + y, center[0] + y, center[0] - y, center[0] - y };
	float yArray[8] = {center[1] + y, center[1] - y, center[1] + y, center[1] - y, center[1] + x, center[1] - x, center[1] + x, center[1] - x };
	for (int i = 0; i < 8; i++) {
		float loc[3] = {xArray[i], yArray[i], 0};
		drawPoint(loc, color, VAO, VBO);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework3::initBools() {
	homework3 = false;
	triangleFrame = false;
	circleFrame = false;
}