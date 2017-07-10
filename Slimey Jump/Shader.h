// File Name	: Shader.h 
// Description	: Sets up Shader class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include "Common.h"
#include "MatrixTransformation.h"
#include "Camera.h"

#include <string>

class Shader
{
public:
	Shader() { /* Do Nothing */ };
	~Shader() { /* Do Nothing */ };

	GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);

	void UpdateTransform(const MatrixTransform&, const Camera&);
	inline void UseProgram() { glUseProgram(m_Program); };
	inline void SetProgram(GLuint X) { m_Program = X; };
	inline GLuint GetProgram() const { return m_Program; };

private:
	enum { MODEL_U, View_U, Proj_U, TOTAL_UNIFORMS };

	std::string ShaderInfoLog(GLuint);
	std::string ProgramInfoLog(GLuint);
	
	std::string LoadShaderFile(char* filename);
	GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName);

	GLuint m_Program;
	GLuint m_uniforms[TOTAL_UNIFORMS];
};

#endif // !__SHADER_H__