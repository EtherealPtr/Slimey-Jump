// File Name	: Texture.h 
// Description	: Sets up Texture class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include <vector>

#include "Dependencies\glew\glew.h"
#include "Dependencies\soil\SOIL.h"

class Texture
{
public:
	Texture();
	~Texture();

	void InitTexture(const std::string&);
	void BindTexture(unsigned int);

private:

	GLuint m_Texture, m_SkyboxTexture;
	int m_Width, m_Height;
};

#endif // !__TEXTURE_H__