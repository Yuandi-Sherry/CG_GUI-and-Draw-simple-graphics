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
	filledTri = false;
}

void Homework3::fillTriangle() {
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
	// find the bound
	float top = triangleVertex[1] > triangleVertex[3] ? triangleVertex[1] : triangleVertex[3];
	top = top > triangleVertex[5] ? top : triangleVertex[5];
	float bottom = triangleVertex[1] < triangleVertex[3] ? triangleVertex[1] : triangleVertex[3];
	bottom = bottom < triangleVertex[5] ? bottom : triangleVertex[5];
	float left = triangleVertex[0] < triangleVertex[2] ? triangleVertex[0] : triangleVertex[2];
	left = left < triangleVertex[4] ? left : triangleVertex[4];
	float right = triangleVertex[0] > triangleVertex[2] ? triangleVertex[0] : triangleVertex[2];
	right = right > triangleVertex[4] ? left : triangleVertex[4];
	float stepX = (float)2 / windowWidth;
	float stepY = (float)2 / windowHeight;
	float edge2[3] = { triangleVertex[0] - triangleVertex[2], triangleVertex[1] - triangleVertex[3], 0 }; // 2 -> 1
	float edge3[3] = { triangleVertex[2] - triangleVertex[4], triangleVertex[3] - triangleVertex[5], 0 }; // 3 -> 2
	float edge1[3] = { triangleVertex[4] - triangleVertex[0], triangleVertex[5] - triangleVertex[1], 0 }; // 1 -> 3

	for (float i = left; i < right; i += stepX) {
		for (float j = bottom; j < top; j += stepY) {
			// 判断点是否在三角形内
			if (isInTri(i, j, edge1, edge2, edge3)) {
				float loc[3] = { i, j, 0.0 };
				drawPoint(loc, color, VAO, VBO);
			}
		}
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

bool Homework3::isInTri(const float & x, const float & y, const float * edge1, const float * edge2, const float * edge3) {
	float P2[2] = { x - triangleVertex[2], y - triangleVertex[3]}; // 2 -> P
	float P3[2] = { x - triangleVertex[4], y - triangleVertex[5]}; // 3 -> P
	float P1[2] = { x - triangleVertex[0], y - triangleVertex[1]}; // 1 -> P

	float cross2 = edge2[0] * P2[1] - edge2[1] * P2[0];
	float cross3 = edge3[0] * P3[1] - edge3[1] * P3[0];
	float cross1 = edge1[0] * P1[1] - edge1[1] * P1[0];

	if (cross2 * cross3 > 0 && cross1 * cross3 > 0 && cross1 * cross2 > 0) {
		return true;
	}
	return false;
}