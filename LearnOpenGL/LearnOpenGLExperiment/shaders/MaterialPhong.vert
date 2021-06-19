#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord; 

out vec3 normal;
out vec3 fragPos;
out vec3 lightPosition;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   normal = normalMatrix * aNormal;
   fragPos = vec3(view* model * vec4(aPos, 1.0));
   TexCoord = aTexCoord;
}