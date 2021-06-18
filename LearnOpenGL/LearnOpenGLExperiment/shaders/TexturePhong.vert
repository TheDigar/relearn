#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 textureCoord;
out vec3 normal;
out vec3 fragPos;
out vec3 lightPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 lightPos;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   textureCoord = aTexCoord;
   normal = normalMatrix * aNormal;
   fragPos = vec3(view* model * vec4(aPos, 1.0));
   lightPosition = vec3( view * vec4(lightPos,1.0));
}