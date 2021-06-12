#version 330 core
out vec4 FragColor;
in vec2 textureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
uniform vec3 lightColor;

void main()
{
   FragColor = vec4(lightColor, 1.0) * mix(texture(texture1, textureCoord),texture(texture2, textureCoord), mixValue);
}
