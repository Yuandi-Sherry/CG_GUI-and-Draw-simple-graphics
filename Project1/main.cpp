#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Homework2.h"
#include "Homework3.h"
#include <stdio.h>
#define N 888
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);
bool readFile(const string & fileName, string & content);
void checkCompile(const int & shader, const int & checkType);
void compileShader(unsigned int & shader, const char * filename, const int & shaderType);

void initGUI(GLFWwindow* window);
void displayGUI(GLFWwindow* window, Homework2 & homework2, Homework3 & homework3);
GLFWwindow* initialize();
int windowWidth = 1200;
int windowHeight = 1200;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
// ��ɫ���ļ�
const char* vertexShaderFile = "shader.vs";
const char* fragmentShaderFile = "shader.fs";
const char* glsl_version = "#version 130";
// ������ɫ
ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);

int main() {
	try {
		GLFWwindow* window = initialize();
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
		
		Homework2 homework2(shaderProgram);
		Homework3 homework3(shaderProgram);
		
		// ��Ⱦѭ��
		// ÿ��ѭ����ʼǰ���GLFW�Ƿ��˳�
		while (!glfwWindowShouldClose(window)) {
			// ��鴥���¼������´��ڣ��ص�
			glfwPollEvents();
			displayGUI(window, homework2, homework3);
			
			homework2.displayController();
			homework3.displayController();
			glfwMakeContextCurrent(window);
			// �������塢���ơ���ʾ
			glfwSwapBuffers(window);
		}

		// �ͷ�/ɾ����Դ
		glfwTerminate();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}	
	return 0;
}

GLFWwindow* initialize() {
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw "fail to init glfw";
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ��������
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CG_HOMEWORK2", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw "fail to init window";
	}
	// �������Ĵ��ڵ���������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // Enable vsync
	// ��ʼ��GLAD������ϵͳ���OpenGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw "fail to load glad";
	}
	// init GUI
	initGUI(window);
	return window;
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

void displayGUI(GLFWwindow* window, Homework2 & homework2, Homework3 & homework3) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// ��ɫѡ�񴰿�ϸ��
	ImGui::Begin("Options", NULL, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		homework2.imGuiMenuSetting();
		homework3.imGuiMenuSetting();
		ImGui::EndMenuBar();
	}
	homework2.imGuiSetting();
	homework3.imGuiSetting();
	//if (homework3.homework3) {
	//	ImGui::Checkbox("Triangle Frame", &homework3.triangleFrame);
	//	ImGui::Checkbox("Circle Frame", &homework3.circleFrame);
	//	
	//	homework2.homework2 = false;
	//}

	//if (homework2.homework2) {
	//	ImGui::Checkbox("Triangle", &homework2.triangle);
	//	ImGui::ColorEdit3("Triangle color", (float*)&homework2.triangleColor);
	//	ImGui::Checkbox("Point", &homework2.point);
	//	ImGui::Checkbox("Line", &homework2.line);
	//	ImGui::Checkbox("Bonus", &homework2.bonus);
	//	if (homework2.bonus) {
	//		ImGui::Checkbox("Square", &homework2.rectangle);
	//		ImGui::Checkbox("Several Triangle", &homework2.severalTri);
	//	}
	//	homework3.homework3 = false;
	//}
	ImGui::End();
	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(-1, 1, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}