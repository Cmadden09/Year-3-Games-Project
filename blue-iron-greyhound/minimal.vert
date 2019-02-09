//vertex shader


#version 330

in vec3 in_position;
in vec3 in_Color;
out vec3 ex_Color;

void main(void)
{
	ex_Color = in_Color;
	gl_Position = vec4(in_position, 1.0);
}