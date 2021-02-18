#version 430

in vec4 Color;
out vec4 color;

uniform mat4 mv_matrix;

void main(void)
{	color = Color;
}
