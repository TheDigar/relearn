#version 330 core
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 shininess;
};

struct Light{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;
in vec3 normal;
in vec3 fragPos;
in vec3 lightPosition;

uniform Material material;
uniform Light light;

void main()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir), 0.0), 32);
	vec3 specular = light.specular * (spec * material.specular);

	FragColor = vec4((ambient + diffuse + specular), 1.0);
}
