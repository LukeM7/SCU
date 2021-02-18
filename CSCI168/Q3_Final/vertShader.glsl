#version 430

layout (location=0) in vec3 position;
layout (location=1) in vec4 color;

uniform mat4 mv_matrix;

out vec4 Color;

void main(void)
{	gl_Position = mv_matrix * vec4(position,1.0);
	Color = color;
} 
