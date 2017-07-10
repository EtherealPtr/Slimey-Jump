#version 430 core

// Input
in vec3 Color;
in vec2 Texture;

// Output
out vec4 Fragment_Color;

// Uniforms
uniform sampler2D TextureImage;

void main()
{
	Fragment_Color = texture(TextureImage, Texture);
}
