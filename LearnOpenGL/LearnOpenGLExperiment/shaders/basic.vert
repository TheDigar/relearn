#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;

uniform vec4 position;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f) + position;
   vertexColor = vec4(aColor.r, aColor.g, aColor.b, 1.0f);
}