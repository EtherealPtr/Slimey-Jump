// File Name	: Shapes.h 
// Description	: Sets up Shape class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __SHAPES_H__
#define __SHAPES_H__

#include "Utils.h"

class Shapes
{
public:
	Shapes();
	~Shapes();

	void CreateTriangle();
	void CreateTexturedTriangle();
	void CreateTexturedQuad();

public:
	CVertex_P m_TriangleVertices[3];
	CVertex_PT m_TexturedTriangleVertices[3];
	CVertex_PT m_TexturedQuad[4];
};

#endif // !__SHAPES_H__
