// File Name	: Mesh.h 
// Description	: Sets up Mesh class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __MESH_H__
#define __MESH_H__

//#include "Common.h"
#include "Utils.h"

#include <vector>

using std::vector;

class Mesh
{
public:
	Mesh() {};
	~Mesh();

	void InitGeometry(CVertex_P*, unsigned int, unsigned int*, unsigned int);
	void InitGeometry(CVertex_PT*, unsigned int, unsigned int*, unsigned int);

	void Draw();

private:
	enum { POSITION_VB, COLORS_VB, INDEX_VB, TEXTURE_VB, NORMALS_VB, TOTAL_BUFFERS };

	GLuint m_VAO;
	GLuint m_VBO[TOTAL_BUFFERS];

	unsigned int m_DrawCount;
};

#endif // !__MESH_H__