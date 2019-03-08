#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);
bool readFile(const string & fileName, string & content);
void checkCompile(const int & shader, const int & checkType);
void compileShader(unsigned int & shader, const char * filename, const int & shaderType);
// ��ɫ���ļ�
const char* vertexShaderFile = "shader.vs";
const char* fragmentShaderFile = "shader.fs";


int main() {
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	// ��������
	GLFWwindow* window = glfwCreateWindow(400, 400, "test", NULL, NULL);
	if (window == NULL) {
		cout << "FAIL" << endl;
		glfwTerminate();
		return -1;
	}

	// �������Ĵ��ڵ���������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	// �����ӿ�
	//glViewport(0, 0, 200, 300);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��ʼ��GLAD������ϵͳ���OpenGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "FAIL" << endl;
		return -1;
	}
	
	// --------------- ���������� ---------------

	// ָ�������ζ���
	float vertices[] = {
		-1, -1, 0, 1, 0, 0, 
		 1, -1, 0, 0, 1, 0,
		 0,  1, 0, 0, 0, 1 };
	// VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// �󶨻���
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ��֮ǰ����Ķ��㣨float���飩���Ƶ�������ڴ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// --------------- ������ɫ�� --------------- 
	unsigned int vertexShader;
	compileShader(vertexShader, vertexShaderFile, 1);
	// --------------- Ƭ����ɫ�� --------------- 
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

	// --------------- ���Ӷ������� --------------- 
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// --------------- ����������� --------------- 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ��
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ��ɫ���ԣ�ÿ�����������ɫ����֮�����6float����ÿ��������������ɫ��ƫ����Ϊ3float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ��Ⱦѭ��
	// ÿ��ѭ����ʼǰ���GLFW�Ƿ��˳�
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		// ��Ⱦ
		// ������ɫ
		glClearColor(0, 0, 0, 1);
		// ����
		glClear(GL_COLOR_BUFFER_BIT);
		// ����
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// �������塢���ơ���ʾ
		glfwSwapBuffers(window);
		// ��鴥���¼������´��ڣ��ص�
		glfwPollEvents();

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