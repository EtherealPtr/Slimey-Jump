// File Name	: Shapes.cpp 
// Description	: Shapes class implementation
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#include "Shapes.h"

Shapes::Shapes() { /* Do Nothing */ }
Shapes::~Shapes() { /* Do Nothing */ }

// -------------------
// Author: Rony Hanna
// Description: Function that creates a triangle 
// -------------------
void Shapes::CreateTriangle()
{
	m_TriangleVertices[0].position = { 0.0f, 0.5f, 0.0f };
	m_TriangleVertices[1].position = { 0.5f, -0.5f, 0.0f };
	m_TriangleVertices[2].position = { -0.5f, -0.5f, 0.0f };

	m_TriangleVertices[0].colors = { 0.0f, 1.0f, 0.0f };
	m_TriangleVertices[1].colors = { 1.0f, 0.0f, 0.0f };
	m_TriangleVertices[2].colors = { 1.0f, 0.0f, 1.0f };
}

// -------------------
// Author: Rony Hanna
// Description: Function that creates a triangle with texture coordinates 
// -------------------
void Shapes::CreateTexturedTriangle()
{
	m_TexturedTriangleVertices[0].position = { 0.0f, 0.5f, 0.0f };
	m_TexturedTriangleVertices[1].position = { 0.5f, -0.5f, 0.0f };
	m_TexturedTriangleVertices[2].position = { -0.5f, -0.5f, 0.0f };

	m_TexturedTriangleVertices[0].colors = { 0.0f, 1.0f, 0.0f };
	m_TexturedTriangleVertices[1].colors = { 1.0f, 0.0f, 0.0f };
	m_TexturedTriangleVertices[2].colors = { 1.0f, 0.0f, 1.0f };

	m_TexturedTriangleVertices[0].texture = { 0.5f, 1.0f };
	m_TexturedTriangleVertices[1].texture = { 1.0f, 0.0f };
	m_TexturedTriangleVertices[2].texture = { 0.0f, 0.0f };
}

// -------------------
// Author: Rony Hanna
// Description: Function that creates a quad with texture coordinates 
// -------------------
void Shapes::CreateTexturedQuad()
{
	m_TexturedQuad[0].position = { 0.0f, 0.1f, 0.0f };
	m_TexturedQuad[1].position = { 0.2f, 0.1f, 0.0f };
	m_TexturedQuad[2].position = { 0.2f, -0.1f, 0.0f };
	m_TexturedQuad[3].position = { 0.0f, -0.1f, 0.0f };

	m_TexturedQuad[0].colors = { 0.0f, 1.0f, 0.0f };
	m_TexturedQuad[1].colors = { 1.0f, 0.0f, 0.0f };
	m_TexturedQuad[2].colors = { 1.0f, 0.0f, 1.0f };
	m_TexturedQuad[3].colors = { 0.0f, 1.0f, 1.0f };

	m_TexturedQuad[0].texture = { 0.0f, 1.0f };
	m_TexturedQuad[1].texture = { 1.0f, 1.0f };
	m_TexturedQuad[2].texture = { 1.0f, 0.0f };
	m_TexturedQuad[3].texture = { 0.0f, 0.0f };
}
