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
	GLFWwindow* window = glfwCreateWindow(1200, 800, "CG_HOMEWORK2", NULL, NULL);
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
	// init GUI
	initGUI(window);
	// 初始颜色
	ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);
	ImVec4 triangleColor = ImVec4(-1.0f, -1.0f, -1.0f, 1.00f);
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
	// VBO, VAO
	//unsigned int VBO;
	//unsigned int VAO; // 顶点数组对象 
	//glGenBuffers(1, &VBO);
	//glGenVertexArrays(1, &VAO);
	//// 绑定缓冲
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindVertexArray(VAO);
	//// --------------- 链接顶点属性 --------------- 
	//// 位置属性
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);
	//// 颜色属性
	//// 每两个顶点的颜色属性之间隔着6float，在每个顶点数据内颜色的偏移量为3float
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//glBindVertexArray(0);
	// 改变三角形颜色
	bool dirty = false;
	// 点、线、矩形的显示
	bool showPoint = true;
	bool showLine = true;
	bool showTri = true;
	bool extra = false;
	bool showSevTri = false;
	bool showRec = false;
	// 渲染循环
	// 每次循环开始前检查GLFW是否被退出
	while (!glfwWindowShouldClose(window)) {
		// 检查触发事件、更新窗口，回调
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
			// 指定三角形顶点和颜色
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
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//// 颜色属性
	//// 每两个顶点的颜色属性之间隔着6float，在每个顶点数据内颜色的偏移量为3float
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
		0.5f, 0.5f, 0.0f, 1, 1, 1,   // 右上角
		0.5f, -0.5f, 0.0f, 0, 1, 1,  // 右下角
		-0.5f, -0.5f, 0.0f, 1, 0, 1, // 左下角
		-0.5f, 0.5f, 0.0f, 1, 1, 0   // 左上角
	};
	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
	// 这里的 缓冲类型为GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(0, 200, 400, 400); // 注意视口要加载use之前
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
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//// 颜色属性
	//// 每两个顶点的颜色属性之间隔着6float，在每个顶点数据内颜色的偏移量为3float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glViewport(400, 400, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 2); // 注意这里不是GL_LINE
}

void displayTriangle(const int & shaderProgram, bool & dirty, const ImVec4 & triangleColor) {
	// 三角形初始颜色
	GLfloat triangleVertices[] = {
		 0,  0.5f, 0, 1, 0, 0,
		-0.5f, -0.5f, 0, 0, 1, 0,
		 0.5f, -0.5f, 0, 0, 0, 1 };

	GLfloat vertices[] = {
		0,  0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z,
		-0.5f, -0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z,
		0.5f, -0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z };
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
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

	
	// 绘制
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
	// 颜色选择窗口细节
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
		// 三角形2
		0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 三角形3
		-0.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.4f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 三角形1
		0.0f, -0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 三角形4
		-0.3f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = { 
		0, 1, 2, // 第一个三角形
		3, 4, 5, // 第二个三角形
		6, 7, 8, // 第三个三角形
	    9, 10, 11 // 第四个三角形
	};
	// 索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
	// 这里的 缓冲类型为GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(400, 200, 400, 400); // 注意视口要加载use之前
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

