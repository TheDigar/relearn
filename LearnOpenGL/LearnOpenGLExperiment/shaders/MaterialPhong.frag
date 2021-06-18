#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
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
in vec2 TexCoord;

uniform Material material;
uniform Light light;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoord)));

	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir), 0.0), 32);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoord)));

	FragColor = vec4((ambient + diffuse + specular + vec3(texture(material.emission, TexCoord))), 1.0);
}
