# version 330 core
// ���õ�ǰʹ��GLSL�汾����

// �����޶������ѻ��������������ݰ�����������������������������������
layout (location = 0) in vec3 aPos;

void main() {
	// ���ñ��������涥��λ�õ�������꣬���ĸ�����Ϊ͸����
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}