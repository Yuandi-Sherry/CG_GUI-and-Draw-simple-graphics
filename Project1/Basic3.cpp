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
	GLFWwindow* window = glfwCreateWindow(1280, 720, "test", NULL, NULL);
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
	// set up GUI context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);
	ImVec4 triangleColor = ImVec4(-1.0f, -1.0f, -1.0f, 1.00f);
	// --------------- ���붥�㡢Ƭ����ɫ�� --------------- 
	unsigned int vertexShader;
	compileShader(vertexShader, vertexShaderFile, 1);
	unsigned int fragmentShader;
	compileShader(fragmentShader, fragmentShaderFile, 2);
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
	unsigned int VBO;
	unsigned int VAO; // ����������� 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	// �󶨻���
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// --------------- ���Ӷ������� --------------- 
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);	
	// ��ɫ����
	// ÿ�����������ɫ����֮�����6float����ÿ��������������ɫ��ƫ����Ϊ3float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	// �ı���������ɫ
	bool dirty = false;
	// �����γ�ʼ��ɫ
	GLfloat originalVertices[] = {
		 0,  1, 0, 1, 0, 0,
		-1, -1, 0, 0, 1, 0,
		 1, -1, 0, 0, 0, 1 };
	// �㡢�ߡ����ε���ʾ
	bool showPoint = false;
	bool showLine = false;
	bool showRec = false;
	bool showTri = false;


	// ��Ⱦѭ��
	// ÿ��ѭ����ʼǰ���GLFW�Ƿ��˳�
	while (!glfwWindowShouldClose(window)) {
		// ��鴥���¼������´��ڣ��ص�
		glfwPollEvents();
		// ----------------- imGUI ----------------- 
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// ��ɫѡ�񴰿�ϸ��
		ImGui::Begin("Color Setting");
		ImGui::ColorEdit3("Triangle color", (float*)&triangleColor);
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
		// ----------------- imGUI ----------------- 
		// ----------------- Triangle ----------------- 
		// ָ�������ζ������ɫ
		if (showTri) {
			//GLfloat vertices[] = {
			// 0,  1, 0, triangleColor.x, triangleColor.y, triangleColor.z,
			//-1, -1, 0, triangleColor.x, triangleColor.y, triangleColor.z,
			// 1, -1, 0, triangleColor.x, triangleColor.y, triangleColor.z };
			//if (dirty) {
			//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//}
			//else {
			//	glBufferData(GL_ARRAY_BUFFER, sizeof(originalVertices), originalVertices, GL_STATIC_DRAW);
			//	// judge dirty
			//	if (triangleColor.x > 0) {
			//		dirty = true;
			//	}
			//}
			//// ����
			//glUseProgram(shaderProgram);
			//glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//glBindVertexArray(0);
			//glViewport(0, 0, 400, 400);
		}
		if (!showPoint) {
			glPointSize(2.0f);
			glBegin(GL_POINTS);

			glColor3f(1.0, 0.0, 0.0);    // Red
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.5f, 0.8f);
			glEnd();
		}
		// ----------------- Triangle ----------------- 
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
	auto para = shaderType == 1 ? GL_VERTEX_SHADER: GL_FRAGMENT_SHADER ;
	shader = glCreateShader(para);
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