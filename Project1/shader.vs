# version 330 core
// ���õ�ǰʹ��GLSL�汾����

// �����޶������ѻ��������������ݰ�����������������������������������
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec3 ourColor;

void main() {
	// ���ñ��������涥��λ�õ�������꣬���ĸ�����Ϊ͸����
	gl_Position = vec4(aPos, 1.0);
	ourColor = color;
}