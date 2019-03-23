#include "Homework3.h"
using namespace std;
extern int windowWidth;
extern int windowHeight;
Homework3::Homework3(const int vertices[6], const int & shaderProgram)
{
	initVars();
	this->shaderProgram = shaderProgram;
	setTriangle(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5]);
	setCircle();
	initBound();
}

Homework3::Homework3(const int & centerX, const int & centerY, const int & radius, const int & shaderProgram)
{
	initVars();
	this->shaderProgram = shaderProgram;
	setCircle(centerX, centerY, radius);
	setTriangle();
	initBound();
}

Homework3::Homework3(const int & shaderProgram)
{
	initVars();
	this->shaderProgram = shaderProgram;
	setCircle();
	setTriangle();
	initBound();
}

void Homework3::setTriangle(const int & p1x, const int & p1y, const int & p2x, const int & p2y, const int & p3x, const int & p3y ) {
	point1[0] = p1x;
	point1[1] = p1y;
	point2[0] = p2x;
	point2[1] = p2y;
	point3[0] = p3x;
	point3[1] = p3y;
}

void Homework3::setCircle(const int & centerX, const int & centerY, const int & radius) {
	this->center[0] = centerX;
	this->center[1] = centerY;
	this->radius = radius;
}

void Homework3::drawPoint(const float location[3], const float color[3], const int & VAO) {
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

void Homework3::drawLine(const int startPoint[2], const int endPoint[2], const int & VAO) {
	int deltaX = abs(endPoint[0] - startPoint[0]);
	int deltaY = abs(endPoint[1] - startPoint[1]);
	int y_i = startPoint[1];
	int x_i = startPoint[0];
	// 这里需要判断斜率无穷的情况
	if (deltaX == 0) {
		int stepY = (endPoint[1] - startPoint[1]) / deltaY;
		while (abs(y_i - startPoint[1]) < abs(endPoint[1] - startPoint[1])) {
			float loc[3] = { (float)x_i / windowWidth * 2, (float)y_i / windowHeight * 2 , 0 };
			drawPoint(loc, color, VAO);
			y_i += stepY;
		}
	}
	else if (deltaY == 0) {
		int stepX = (endPoint[0] - startPoint[0]) / deltaX;
		while (abs(x_i - startPoint[0]) < abs(endPoint[0] - startPoint[0])) {
			float loc[3] = { (float)x_i / windowWidth * 2, (float)y_i / windowHeight * 2 , 0 };
			drawPoint(loc, color, VAO);
			x_i = x_i + stepX;
		}
	}
	else {
		int stepY = (endPoint[1] - startPoint[1]) / deltaY;
		int stepX = (endPoint[0] - startPoint[0]) / deltaX;
		// 判断斜率与45°的大小
		if (abs(deltaY / deltaX) < 1) {
			float p_i = 2 * deltaY - deltaX;
			// cout << "stepX" << stepX << endl << "stepY" << stepY << endl;
			while (abs(x_i - startPoint[0]) < abs(endPoint[0] - startPoint[0])) {
				float loc[3] = { (float)x_i / windowWidth * 2, (float)y_i / windowHeight * 2 , 0 };
				drawPoint(loc, color, VAO);
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
				float loc[3] = { (float)x_i / windowWidth * 2, (float)y_i / windowHeight * 2 , 0 };
				drawPoint(loc, color, VAO);
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
	drawLine(point1, point2, VAO);
	drawLine(point1, point3, VAO);
	drawLine(point2, point3, VAO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework3::drawCircle() {
	float d_i = 1-radius;
	float y_i = center[1] + radius;
	float x_i = center[0];
	while (x_i < center[0] + sqrt(2) * radius/2 + 1 ) {
		draw8points(x_i, y_i);
		if (d_i < 0) {
			d_i = d_i + 2*x_i + 3;
		}
		else {
			d_i = d_i + 2*(x_i- y_i) + 5;
			y_i--;
		}
		x_i++;
	}
}

void Homework3::draw8points(const int & x, const int & y) {
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
	int deltaX = x - center[0];
	int deltaY = y - center[1];
	int xArray[8] = {center[0] + deltaX, center[0] + deltaX, center[0] - deltaX, center[0] - deltaX, center[0] + deltaY, center[0] + deltaY, center[0] - deltaY, center[0] - deltaY };
	int yArray[8] = {center[1] + deltaY, center[1] - deltaY, center[1] + deltaY, center[1] - deltaY, center[1] + deltaX, center[1] - deltaX, center[1] + deltaX, center[1] - deltaX };
	for (int i = 0; i < 8; i++) {
		float loc[3] = {(float)xArray[i] / windowWidth * 2, (float)yArray[i] / windowHeight * 2, 0};
		drawPoint(loc, color, VAO);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework3::initVars() {
	triangleFrame = false;
	circleFrame = false;
	filledTri = false;
}

void Homework3::initBound() {
	top = point1[1] > point2[1] ? point1[1] : point2[1];
	top = top > point3[1] ? top : point3[1];
	bottom = point1[1] < point2[1] ? point1[1] : point2[1];
	bottom = bottom < point3[1] ? bottom : point3[1];
	left = point1[0] < point2[0] ? point1[0] : point2[0];
	left = left < point3[0] ? left : point3[0];
	right = point1[0] > point2[0] ? point1[0] : point2[0];
	right = right > point3[0] ? right : point3[0];
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
	int edge2[3] = { point1[0] - point2[0], point1[1] - point2[1], 0 }; // 2 -> 1
	int edge3[3] = { point2[0] - point3[0], point2[1] - point3[1], 0 }; // 3 -> 2
	int edge1[3] = { point3[0] - point1[0], point3[1] - point1[1], 0 }; // 1 -> 3
	for (float i = left; i < right; i++) {
		for (float j = bottom; j < top; j++) {
			// 判断点是否在三角形内
			if (isInTri(i, j, edge1, edge2, edge3)) {
				float loc[3] = { (float) i / windowWidth * 2, (float)j / windowHeight * 2, 0.0 };
				drawPoint(loc, color, VAO);
			}
		}
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

bool Homework3::isInTri(const int & x, const int & y, const int * edge1, const int * edge2, const int * edge3) {
	float P2[2] = { x - point2[0], y - point2[1] }; // 2 -> P
	float P3[2] = { x - point3[0], y - point3[1]}; // 3 -> P
	float P1[2] = { x - point1[0], y - point1[1]}; // 1 -> P

	float cross2 = edge2[0] * P2[1] - edge2[1] * P2[0];
	float cross3 = edge3[0] * P3[1] - edge3[1] * P3[0];
	float cross1 = edge1[0] * P1[1] - edge1[1] * P1[0];
 	if (cross2 * cross3 > 0 && cross1 * cross3 > 0 && cross1 * cross2 > 0) {
		return true;
	}
	return false;
}

void Homework3::displayController() {
	if (triangleFrame) {
		drawTriangle();
	}
	if (circleFrame) {
		drawCircle();
	}
	if (filledTri) {
		fillTriangle();
	}
}

/*-------------------------- GUI SETTINGS --------------------------*/
void Homework3::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework3"))
	{
		if (ImGui::BeginMenu("Basic"))
		{
			ImGui::MenuItem("Triangle", NULL, &triangleFrame);
			ImGui::MenuItem("Circle", NULL, &circleFrame);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Bonus"))
		{
			ImGui::MenuItem("Fill Triangle", NULL, &filledTri);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}	
}

void Homework3::imGuiSetting() {
	if (circleFrame) {
		ImGui::InputInt("X", &center[0]);
		ImGui::InputInt("Y", &center[1]);
		ImGui::InputInt("Radius", &radius);
	}
	if (triangleFrame) {
		ImGui::InputInt2("Point1", point1);
		ImGui::InputInt2("Point2", point2);
		ImGui::InputInt2("Point3", point3);
		initBound();
	}
}

