#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;


uniform mat4 mTransform;
uniform sampler2D theOtherTexture;

out vec2 texCoord;

void main()
{
	vec4 nPos = vPosition;
	texCoord = vTexCoord;
	vec4 fColor = texture(theOtherTexture, texCoord);
	float Lumi = 0.299 * fColor.r + 0.587 * fColor.g + 0.114 * fColor.b;
	nPos.y = (10 * Lumi);
	gl_Position = mTransform * nPos;
}