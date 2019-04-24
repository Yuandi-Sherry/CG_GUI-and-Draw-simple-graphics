#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPosition;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
	// 环境光照
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// 漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);
	float diff = max(dot(norm, lightDir), 0.0); // 处理夹角>90的情况
	vec3 diffuse = diff * lightColor;

	// 镜面反射
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos); // 视线方向
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 - 反光度
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}
