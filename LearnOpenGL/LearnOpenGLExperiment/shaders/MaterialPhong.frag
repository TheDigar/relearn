#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	vec3 shininess;
};

struct PointLight{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

out vec4 FragColor;
in vec3 normal;
in vec3 fragPos;
in vec2 TexCoord;

#define NPointLights 4
uniform Material material;
uniform PointLight pointLights;

vec4 ComputePointLight()
{
	vec3 viewDir = normalize(-fragPos);
	vec3 norm = normalize(normal);

	vec3 lightDir = normalize(vec3(pointLights.position) - fragPos);
	float dist = length(vec3(pointLights.position) - fragPos);
	float attenuation = 1.0/(pointLights.constant + pointLights.linear*dist +pointLights.quadratic*(dist*dist));

	vec3 ambient = pointLights.ambient * vec3(texture(material.diffuse, TexCoord));
	
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = pointLights.diffuse * (diff * vec3(texture(material.diffuse, TexCoord)));

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir), 0.0), 32);
	vec3 specular = pointLights.specular * (spec * vec3(texture(material.specular, TexCoord)));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return vec4((ambient + diffuse + specular + vec3(texture(material.emission, TexCoord))), 1.0);
}

void main()
{
	vec3 lightDir;
	float attenuation = 1.0;
//	if(light.direction.w == 0.0)
//	{
//		lightDir = normalize(vec3(-light.direction));
//	}
//	else


	FragColor = vec4(0.0);
	FragColor += ComputePointLight();
}
