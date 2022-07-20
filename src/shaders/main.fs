#version 330 core

out vec4 FragColor;
uniform sampler2D objectTexture;
in vec2 texPos;

void main()
{

	FragColor = texture(objectTexture, texPos);
}