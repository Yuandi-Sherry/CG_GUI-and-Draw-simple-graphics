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
// 着色器文件
const char* vertexShaderFile = "shader.vs";
const char* fragmentShaderFile = "shader.fs";
const char* glsl_version = "#version 130";
// 清屏颜色
ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);

int main() {
	try {
		GLFWwindow* window = initialize();
		// --------------- 编译顶点、片段着色器 --------------- 
		unsigned int vertexShader;
		compileShader(vertexShader, vertexShaderFile, GL_VERTEX_SHADER);
		unsigned int fragmentShader;
		compileShader(fragmentShader, fragmentShaderFile, GL_FRAGMENT_SHADER);
		// --------------- 着色器程序 --------------- 
		unsigned int shaderProgram;
		// 创建程序，返回ID引用
		shaderProgram = glCreateProgram();
		// 链接
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		checkCompile(shaderProgram, 2);
		// 激活程序对象
		glUseProgram(shaderProgram);
		// 新建作业对象
		Homework2 homework2(shaderProgram);
		Homework3 homework3(shaderProgram);
		
		// 渲染循环
		// 每次循环开始前检查GLFW是否被退出
		while (!glfwWindowShouldClose(window)) {
			// 检查触发事件、更新窗口，回调
			glfwPollEvents();
			displayGUI(window, homework2, homework3);
			// 作业对象的显示控制
			homework2.displayController();
			homework3.displayController();
			glfwMakeContextCurrent(window);
			// 交换缓冲、绘制、显示
			glfwSwapBuffers(window);
		}

		// 释放/删除资源
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
	// 初始化GLFW
	glfwInit();
	// 设置GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CG_HOMEWORK2", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw "fail to init window";
	}
	// 将创建的窗口的上下文设为当前线程的主上下文
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // Enable vsync
	// 初始化GLAD，加载系统相关OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw "fail to load glad";
	}
	// init GUI
	initGUI(window);
	return window;
}
/*
 * 鼠标调整后的新的大小为后两个参数
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
/*
 * 处理输入
 */
void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
/*
 * 文件读取
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
 * 编译着色器
 @shader 着色器
 @filename 着色器文件名
 @type 着色器类别 1->vertex, 2->fragment
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
	ImGui::Begin("Options", NULL, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		// 作业GUI显示
		homework2.imGuiMenuSetting();
		homework3.imGuiMenuSetting();
		ImGui::EndMenuBar();
	}
	homework2.imGuiSetting();
	homework3.imGuiSetting();

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