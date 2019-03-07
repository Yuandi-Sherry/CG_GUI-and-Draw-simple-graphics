#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);
int main() {
	// 初始化GLFW
	glfwInit();
	// 设置GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (window == NULL) {
		cout << "FAIL" << endl;
		glfwTerminate();
		return -1;
	}

	// 将创建的窗口的上下文设为当前线程的主上下文
	glfwMakeContextCurrent(window);
	// 创建视口
	//glViewport(0, 0, 200, 300);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 初始化GLAD，加载系统相关OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "FAIL" << endl;
		return -1;
	}
	
	
	// 渲染循环
	// 每次循环开始前检查GLFW是否被退出
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		// 渲染
		// 清屏颜色
		glClearColor(1, 1, 1, 1);
		// 清屏
		glClear(GL_COLOR_BUFFER_BIT);
		// 交换缓冲、绘制、显示
		glfwSwapBuffers(window);
		// 检查触发事件、更新窗口，回调
		glfwPollEvents();

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
