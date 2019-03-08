# version 330 core
// 设置当前使用GLSL版本名称

// 布局限定符，把缓冲区索引的数据绑定输入输出，并声明三个浮点数的输入变量
layout (location = 0) in vec3 aPos;

void main() {
	// 内置变量，保存顶点位置的齐次坐标，第四个分量为透明度
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}