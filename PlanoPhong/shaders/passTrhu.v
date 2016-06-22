#version 430 core

layout (location = 0) in vec4 vPosition;

uniform mat4 mTransform;
uniform float fTime;

vec4 mathFunc (vec4 r)
{
	r.y = 2.0 *cos(fTime)* sin(0.01 * (r.x * r.x + r.z * r.z)+fTime);
	return r;
}

void main()
{
	gl_Position = mTransform * mathFunc(vPosition);
}