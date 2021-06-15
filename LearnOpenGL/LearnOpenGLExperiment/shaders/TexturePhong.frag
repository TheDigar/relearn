#version 330 core
out vec4 FragColor;
in vec2 textureCoord;
in vec3 normal;
in vec3 fragPos;
in vec3 lightPosition;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
uniform vec3 lightColor;

void main()
{
	float ambientStrenght = 0.2;
	float specularStrenght = 0.8;
	vec3 ambient = ambientStrenght * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir), 0.0), 32);
	vec3 specular = specularStrenght * spec * lightColor;

	FragColor = vec4((ambient + diffuse + specular), 1.0) * mix(texture(texture1, textureCoord),texture(texture2, textureCoord), mixValue);
}
