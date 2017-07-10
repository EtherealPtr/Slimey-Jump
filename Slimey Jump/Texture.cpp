// File Name	: Texture.cpp 
// Description	: Texture class implementation
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz
 
#include "Texture.h"
#include <cassert>
#include <iostream>

Texture::Texture() { /* Do Nothing */ }

Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void Texture::InitTexture(const std::string& path)
{
	unsigned char* pTextureImage = SOIL_load_image(path.c_str(), &m_Width, &m_Height, 0, SOIL_LOAD_RGBA);

	if (pTextureImage == nullptr)
		std::cerr << "ERROR: Error while loading texture image.\n";
	
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture Filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pTextureImage);

	SOIL_free_image_data(pTextureImage);
}

void Texture::BindTexture(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}