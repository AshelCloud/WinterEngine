#version 330 core

in vec3 positionAttribute;
in vec3 colorAttribute;
out vec3 passColorAttribute;

void main()
{
	gl_Position = vec4(positionAttribute, 1.0);
	passColorAttribute = colorAttribute;
}