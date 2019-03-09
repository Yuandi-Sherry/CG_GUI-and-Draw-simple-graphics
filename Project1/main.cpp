#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);
bool readFile(const string & fileName, string & content);
void checkCompile(const int & shader, const int & checkType);
void compileShader(unsigned int & shader, const char * filename, const int & shaderType);
void displayPoint(const int & shaderProgram);
void displayLine(const int & shaderProgram);
void displayRec(const int & shaderProgram);
void displayLine(const int & shaderProgram);
void displayTriangle(const int & shaderProgram, bool & dirty, const ImVec4 & triangleColor);
void initGUI(GLFWwindow* window);
void displayGUI(GLFWwindow* window, bool & showPoint, bool & showLine, bool & showTri, bool & showRec, bool & extra, bool & showSevTri, ImVec4& triangleColor, const ImVec4& clear_color);
void displaySeveralTriangle(const int & shaderProgram/*, const int & VAO, const int & VBO*/);

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
// ��ɫ���ļ�
const char* vertexShaderFile = "shader.vs";
const char* fragmentShaderFile = "shader.fs";
const char* glsl_version = "#version 130";

int main() {
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ��������
	GLFWwindow* window = glfwCreateWindow(1200, 800, "CG_HOMEWORK2", NULL, NULL);
	if (window == NULL) {
		cout << "FAIL" << endl;
		glfwTerminate();
		return -1;
	}
	// �������Ĵ��ڵ���������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // Enable vsync
	// ��ʼ��GLAD������ϵͳ���OpenGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "FAIL" << endl;
		return -1;
	}
	// init GUI
	initGUI(window);
	// ��ʼ��ɫ
	ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);
	ImVec4 triangleColor = ImVec4(-1.0f, -1.0f, -1.0f, 1.00f);
	// --------------- ���붥�㡢Ƭ����ɫ�� --------------- 
	unsigned int vertexShader;
	compileShader(vertexShader, vertexShaderFile, GL_VERTEX_SHADER);
	unsigned int fragmentShader;
	compileShader(fragmentShader, fragmentShaderFile, GL_FRAGMENT_SHADER);
	// --------------- ��ɫ������ --------------- 
	unsigned int shaderProgram;
	// �������򣬷���ID����
	shaderProgram = glCreateProgram();
	// ����
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkCompile(shaderProgram, 2);
	// ����������
	glUseProgram(shaderProgram);
	// VBO, VAO
	//unsigned int VBO;
	//unsigned int VAO; // ����������� 
	//glGenBuffers(1, &VBO);
	//glGenVertexArrays(1, &VAO);
	//// �󶨻���
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindVertexArray(VAO);
	//// --------------- ���Ӷ������� --------------- 
	//// λ������
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);
	//// ��ɫ����
	//// ÿ�����������ɫ����֮�����6float����ÿ��������������ɫ��ƫ����Ϊ3float
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//glBindVertexArray(0);
	// �ı���������ɫ
	bool dirty = false;
	// �㡢�ߡ����ε���ʾ
	bool showPoint = true;
	bool showLine = true;
	bool showTri = true;
	bool extra = false;
	bool showSevTri = false;
	bool showRec = false;
	// ��Ⱦѭ��
	// ÿ��ѭ����ʼǰ���GLFW�Ƿ��˳�
	while (!glfwWindowShouldClose(window)) {
		// ��鴥���¼������´��ڣ��ص�
		glfwPollEvents();
		displayGUI(window, showPoint, showLine, showTri, showRec, extra, showSevTri,triangleColor, clear_color);
		if (extra) {
			if (showRec) {
				displayRec(shaderProgram);
			}
			if(showSevTri)
				displaySeveralTriangle(shaderProgram/*, VAO, VBO*/);
		}
		else {
			// ָ�������ζ������ɫ
			if (showTri) {
				displayTriangle(shaderProgram, dirty, triangleColor);
			}
			if (showPoint) {
				displayPoint(shaderProgram);
			}
			if (showLine) {
				displayLine(shaderProgram);
			}
			
		}
		glfwMakeContextCurrent(window);
		// �������塢���ơ���ʾ
		glfwSwapBuffers(window);
	}

	// �ͷ�/ɾ����Դ
	glfwTerminate();
	return 0;
}
/*
 * ����������µĴ�СΪ����������
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
/*
 * ��������
 */
void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
/*
 * �ļ���ȡ
 */
bool readFile(const string & fileName, string & content) {
	ifstream inFile(fileName);
	if (!inFile) {
		cout << "Fail to read " << fileName.c_str() << endl;
		return false;
	}
	else {
		string line;
		while (getline(inFile, line)) {
			content.append(line);
			content.append("\n");
		}
	}
	return true;
}

void checkCompile(const int & shader, const int & checkType) {
	int success;
	char info[512];
	if (checkType == 1) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			cout << "COMPILE ERROR: " << endl;
			glGetShaderInfoLog(shader, 512, NULL, info);
			cout << info << endl;
		}
	}
	else if (checkType == 2) {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			cout << "COMPILE ERROR: " << endl;
			glGetProgramInfoLog(shader, 512, NULL, info);
			cout << info << endl;
		}
	}
}
/*
 * ������ɫ��
 @shader ��ɫ��
 @filename ��ɫ���ļ���
 @type ��ɫ����� 1->vertex, 2->fragment
 */
void compileShader(unsigned int & shader, const char * filename, const int & shaderType) {
	shader = glCreateShader(shaderType);
	string shaderSource;
	if (readFile(filename, shaderSource)) {
		const GLchar* p[1];
		p[0] = shaderSource.c_str();
		GLint Lengths[1];
		Lengths[0] = strlen(shaderSource.c_str());
		glShaderSource(shader, 1, p, Lengths);
		glCompileShader(shader);
		checkCompile(shader, 1);
	}
	else {
		cout << "Fail to read shader file" << endl;
	}
}

void displayPoint(const int & shaderProgram/*, const int & VAO*/) {
	float pointVertex[] = {
		0, 0, 0, 1, 1, 1
	};
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//// ��ɫ����
	//// ÿ�����������ɫ����֮�����6float����ÿ��������������ɫ��ƫ����Ϊ3float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertex), pointVertex, GL_STATIC_DRAW);
	glViewport(400, 0, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 1);
}

void displayRec(const int & shaderProgram/*, const int & VAO, const int & VBO*/) {
	float recVertices[] = {
		0.5f, 0.5f, 0.0f, 1, 1, 1,   // ���Ͻ�
		0.5f, -0.5f, 0.0f, 0, 1, 1,  // ���½�
		-0.5f, -0.5f, 0.0f, 1, 0, 1, // ���½�
		-0.5f, 0.5f, 0.0f, 1, 1, 0   // ���Ͻ�
	};
	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// �����������
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
	// ����� ��������ΪGL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(0, 200, 400, 400); // ע���ӿ�Ҫ����use֮ǰ
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void displayLine(const int & shaderProgram) {
	float lineVertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//// ��ɫ����
	//// ÿ�����������ɫ����֮�����6float����ÿ��������������ɫ��ƫ����Ϊ3float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glViewport(400, 400, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 2); // ע�����ﲻ��GL_LINE
}

void displayTriangle(const int & shaderProgram, bool & dirty, const ImVec4 & triangleColor) {
	// �����γ�ʼ��ɫ
	GLfloat triangleVertices[] = {
		 0,  0.5f, 0, 1, 0, 0,
		-0.5f, -0.5f, 0, 0, 1, 0,
		 0.5f, -0.5f, 0, 0, 0, 1 };

	GLfloat vertices[] = {
		0,  0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z,
		-0.5f, -0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z,
		0.5f, -0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z };
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	if (dirty) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
		// judge dirty
		if (triangleColor.x > 0) {
			dirty = true;
		}
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	
	// ����
	glViewport(0, 0, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void initGUI(GLFWwindow* window) {
	// set up GUI context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void displayGUI(GLFWwindow* window, bool & showPoint, bool & showLine, bool & showTri, bool & showRec, bool & extra, bool & showSevTri, ImVec4& triangleColor, const ImVec4& clear_color) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// ��ɫѡ�񴰿�ϸ��
	ImGui::Begin("Color Setting");
	ImGui::Checkbox("Change to several triangles", &extra);
	if (!extra) {
		ImGui::Checkbox("Point", &showPoint);
		ImGui::Checkbox("Line", &showLine);
		ImGui::Checkbox("Triangle", &showTri);
		ImGui::ColorEdit3("Triangle color", (float*)&triangleColor);
	}
	else {
		ImGui::Checkbox("Several Triangles", &showSevTri);
		ImGui::Checkbox("Rectangle", &showRec);
	}
	ImGui::End();
	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void displaySeveralTriangle(const int & shaderProgram) {

	float recVertices[] = {
		// ������2
		0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
		// ������3
		-0.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.4f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,
		// ������1
		0.0f, -0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// ������4
		-0.3f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = { 
		0, 1, 2, // ��һ��������
		3, 4, 5, // �ڶ���������
		6, 7, 8, // ������������
	    9, 10, 11 // ���ĸ�������
	};
	// �����������
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
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
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

