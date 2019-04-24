#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPosition;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
	// 环境光照
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// 漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);
	float diff = max(dot(norm, lightDir), 0.0); // 处理夹角>90的情况
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);
}
