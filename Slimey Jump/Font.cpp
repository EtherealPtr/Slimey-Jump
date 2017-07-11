// File Name	: Font.cpp 
// Description	: Font class implementation
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

// Local includes
#include "Font.h"

// -------------------
// Author: Rony Hanna
// Description: Initialize font components 
// -------------------
Text::Text(std::string text, std::string font)
{
	this->m_Text = text;
	this->m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_Scale = 1.0f;

	this->SetPosition(m_Position);

	Shader shaderText;
	TextProgram = shaderText.CreateProgram("Assets/Shaders/Text.vs", "Assets/Shaders/Text.fs");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800.0f), 0.0f, static_cast<GLfloat>(600.0f));

	glUseProgram(TextProgram);
	glUniformMatrix4fv(glGetUniformLocation(TextProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	FT_Library ft;

	if (FT_Init_FreeType(&ft))
		std::cout << "Error, failed to initialize FreeType Library.\n";

	FT_Face face;

	if (FT_New_Face(ft, font.c_str(), 0, &face))
		std::cout << "Error, failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Error, failed to load glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		Characters.insert(std::pair<GLchar, Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// -------------------
// Author: Rony Hanna
// Description: Function that renders font
// -------------------
void Text::Render()
{
	glm::vec2 textPos = this->m_Position;

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Activate corresponding render state	
	glUseProgram(TextProgram);
	glUniform3f(glGetUniformLocation(TextProgram, "textColor"), this->m_Color.x, this->m_Color.y, this->m_Color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = m_Text.begin(); c != m_Text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = textPos.x + ch.Bearing.x * this->m_Scale;
		GLfloat ypos = textPos.y - (ch.Size.y - ch.Bearing.y) * this->m_Scale;

		GLfloat w = ch.Size.x * this->m_Scale;
		GLfloat h = ch.Size.y * this->m_Scale;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },

			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

		// Render quad 
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Advance cursors for next glyph 
		textPos.x += (ch.Advance >> 6) * this->m_Scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}