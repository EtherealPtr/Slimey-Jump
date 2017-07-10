#version 430 core

// Attributes
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec2 vertex_texture;

//Output
out vec3 Color;
out vec2 Texture;

// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(vertex_position, 1.0f);
	Color = vertex_color;
	Texture = vertex_texture;
}