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

// 着色器文件
const char* vertexShaderFile = "shader.vs";
const char* fragmentShaderFile = "shader.fs";

const char* glsl_version = "#version 130";

int main() {
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;
	// 初始化GLFW
	glfwInit();
	// 设置GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	
	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(1280, 720, "test", NULL, NULL);
	if (window == NULL) {
		cout << "FAIL" << endl;
		glfwTerminate();
		return -1;
	}
	// 将创建的窗口的上下文设为当前线程的主上下文
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // Enable vsync
	// 初始化GLAD，加载系统相关OpenGL函数指针
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
	ImVec4 triangleColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// --------------- 编译顶点、片段着色器 --------------- 
	unsigned int vertexShader;
	compileShader(vertexShader, vertexShaderFile, 1);
	unsigned int fragmentShader;
	compileShader(fragmentShader, fragmentShaderFile, 2);
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
	// VBO, VAO
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	// 绑定缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// --------------- 链接顶点属性 --------------- 
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);	
	// 颜色属性
	// 每两个顶点的颜色属性之间隔着6float，在每个顶点数据内颜色的偏移量为3float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// 渲染循环
	// 每次循环开始前检查GLFW是否被退出
	while (!glfwWindowShouldClose(window)) {
		// 检查触发事件、更新窗口，回调
		glfwPollEvents();
		// ----------------- imGUI ----------------- 
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// 颜色选择窗口细节
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
		// 指定三角形顶点和颜色
		GLfloat vertices[] = {
			 0,  1, 0, triangleColor.x, triangleColor.y, triangleColor.z,
			-1, -1, 0, triangleColor.x, triangleColor.y, triangleColor.z,
			 1, -1, 0, triangleColor.x, triangleColor.y, triangleColor.z };
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// processInput(window);
		// 渲染
		// 清屏颜色
		// glClearColor(0.5, 0.5, 0.5, 1);
		// 清屏
		// glClear(GL_COLOR_BUFFER_BIT);
		// 绘制
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glViewport(0, 0, 1280, 720);
		glfwMakeContextCurrent(window);
		// 交换缓冲、绘制、显示
		glfwSwapBuffers(window);
	}

	// 释放/删除资源
	glfwTerminate();
	return 0;
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