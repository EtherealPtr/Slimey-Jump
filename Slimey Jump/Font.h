// File Name	: Font.h 
// Description	: Class that sets up text 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __FONT_H__
#define __FONT_H__

#include "Common.h"
#include "shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <iostream>

struct Character
{
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class Text
{
public:
	Text() {};
	Text(std::string text, std::string font);
	~Text() { /* Do Nothing */ };

	void Render();
	void SetPosition(glm::vec2 Position) { this->m_Position = Position; }
	void SetColor(glm::vec3 Color) { this->m_Color = Color; }
	void SetScale(GLfloat Scale) { this->m_Scale = Scale; }
	void SetText(std::string Text) { this->m_Text = Text; }

	GLuint VAO, VBO, TextProgram = 0;
	std::map<GLchar, Character> Characters;

private:
	std::string m_Text;
	GLfloat m_Scale;
	glm::vec3 m_Color;
	glm::vec2 m_Position;
};

#endif // !__FONT_H__