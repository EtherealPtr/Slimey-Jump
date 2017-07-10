// File Name	: Shader.cpp 
// Description	: Shader class implementation
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#include "Shader.h"
#include <fstream>

using std::getline;
using std::cout;

// -------------------
// Author: Rony Hanna
// Description: Function that returns updated components to the GPU
// -------------------
void Shader::UpdateTransform(const MatrixTransform& transformation, const Camera& camera)
{
	m_uniforms[Proj_U] = glGetUniformLocation(m_Program, "Projection");
	glm::mat4 ProjMatrix = camera.GetProjectionMatrix();
	glUniformMatrix4fv(m_uniforms[Proj_U], 1, GL_FALSE, &ProjMatrix[0][0]);

	m_uniforms[View_U] = glGetUniformLocation(m_Program, "View");
	glm::mat4 ViewMatrix = camera.ViewMatrix();
	glUniformMatrix4fv(m_uniforms[View_U], 1, GL_FALSE, &ViewMatrix[0][0]);

	m_uniforms[MODEL_U] = glGetUniformLocation(m_Program, "Model");
	glm::mat4 ModelMatrix = transformation.GetModel();
	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &ModelMatrix[0][0]);
}

// -------------------
// Author: Rony Hanna
// Description: Function that returns the name of the shader passed to it 
// -------------------
std::string ShaderTypeName(GLuint shader)
{
	if (glIsShader(shader))
	{
		GLint shaderType = 0;
		glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);

		if (shaderType == GL_VERTEX_SHADER)
			return "Vertex Shader";
		if (shaderType == GL_TESS_CONTROL_SHADER)
			return "Tessellation Control Shader";
		if (shaderType == GL_TESS_EVALUATION_SHADER)
			return "Tessellation Evaluation Shader";
		if (shaderType == GL_GEOMETRY_SHADER)
			return "Geometry Shader";
		if (shaderType == GL_FRAGMENT_SHADER)
			return "Fragment Shader";
		if (shaderType == GL_COMPUTE_SHADER)
			return "Compute Shader";
	}

	return "Invalid shader";
}

// -------------------
// Author: Rony Hanna
// Description: Function that displays shader log
// -------------------
std::string Shader::ShaderInfoLog(GLuint shader)
{
	if (glIsShader(shader))
	{
		GLint logsize = 0;
		GLchar infolog[1024] = { 0 };
		glGetShaderInfoLog(shader, 1024, &logsize, infolog);

		return std::string(infolog);
	}

	return "Invalid shader";
}

// -------------------
// Author: Rony Hanna
// Description: Function that displays program log
// -------------------
std::string Shader::ProgramInfoLog(GLuint program)
{
	if (glIsProgram(program))
	{
		GLint logsize = 0;
		GLchar infolog[1024] = { 0 };
		glGetProgramInfoLog(program, 1024, &logsize, infolog);

		return std::string(infolog);
	}

	return "Invalid program";
}

// -------------------
// Author: Rony Hanna
// Description: Function that reads a shader file
// -------------------
std::string Shader::LoadShaderFile(char* Filename)
{
	std::string ShaderCode;
	std::ifstream File(Filename, std::ios::in);

	if (!File.good())
	{
		std::cout << "ERROR reading shader file: " << Filename << "\n";
		std::terminate();
	}

	File.seekg(0, std::ios::end);
	ShaderCode.resize((unsigned int)File.tellg());
	File.seekg(0, std::ios::beg);
	File.read(&ShaderCode[0], ShaderCode.size());

	File.close();
	return ShaderCode;
}

// -------------------
// Author: Rony Hanna
// Description: Function that creates a shader
// -------------------
GLuint Shader::CreateShader(GLenum ShaderType, std::string Source, char* ShaderName)
{
	int CompileStatus = 0;

	GLuint Shader = glCreateShader(ShaderType);
	const char* ShaderCodePtr = Source.c_str();
	const int ShaderCodeSize = Source.size();

	glShaderSource(Shader, 1, &ShaderCodePtr, &ShaderCodeSize);
	glCompileShader(Shader);

#pragma region ERROR_HANDLING
	{
		std::string GetLogInformation = "";
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompileStatus);
		GetLogInformation = ShaderInfoLog(Shader);

		if (CompileStatus == GL_FALSE)
		{
			std::cout << "ERROR: Shader compilation: " << ShaderName << "\n";
			std::cout << GetLogInformation << "\n";
			return -1;
		}
		else
		{
			std::cout << GetLogInformation << "\n";
		}
	}
#pragma endregion // ERROR_HANDLING

	return Shader;
}


// -------------------
// Author: Rony Hanna
// Description: Function that creates a shader program  
// -------------------
GLuint Shader::CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename)
{
	int LinkingResult = 0;

	// Read shader files and save ID
	std::string VertexShaderID = LoadShaderFile(VertexShaderFilename);
	std::string FragmentShaderID = LoadShaderFile(FragmentShaderFilename);

	GLuint VertexShader = CreateShader(GL_VERTEX_SHADER, VertexShaderID, "Vertex shader");
	GLuint FragmentShader = CreateShader(GL_FRAGMENT_SHADER, FragmentShaderID, "Fragment shader");

	// Creates program, attach shaders, and link shaders
	GLuint program = glCreateProgram();
	glAttachShader(program, VertexShader);
	glAttachShader(program, FragmentShader);

	glLinkProgram(program);

#pragma region ERROR_HANDLING
	{
		std::string ProgramLogInformation;
		glGetProgramiv(program, GL_LINK_STATUS, &LinkingResult);
		ProgramLogInformation = ProgramInfoLog(program);

		if (LinkingResult == GL_FALSE)
		{
			std::cout << "ERROR: Linking Operation Failed. \n";
			return -1;
		}
	}
#pragma endregion // ERROR_HANDLING

	return program;
}