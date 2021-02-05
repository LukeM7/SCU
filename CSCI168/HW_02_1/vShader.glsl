#version 430

mat4 buildRotate(float rad)
{
	mat4 yrot = mat4(cos(rad),0.0,sin(rad),0.0,
			0.0,1.0,0.0,0.0,
			-sin(rad),0.0,cos(rad),0.0,
			0.0,0.0,0.0,1.0);
	return yrot;
}

void main()
{
	if(gl_VertexID == 0) gl_Position = vec4(0.25,-0.25,0.0,1.0) * buildRotate(90);
	else if(gl_VertexID == 1) gl_Position = vec4(-0.25,-0.25,0.0,1.0) * buildRotate(90);
	else gl_Position = vec4(0.25,0.25,0.0,1.0) * buildRotate(90);
}