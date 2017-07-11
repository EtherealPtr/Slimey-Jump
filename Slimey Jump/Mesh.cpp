// File Name	: Mesh.cpp 
// Description	: Mesh class implementation
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#include "Mesh.h"

// -------------------
// Author: Rony Hanna
// Description: Destructor that deletes VAO 
// -------------------
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
}

// -------------------
// Author: Rony Hanna
// Description: Function that sends position and color data to the GPU 
// -------------------
void Mesh::InitGeometry(CVertex_P* Vertices, unsigned int numOfVertices, unsigned int* indices, unsigned int numOfIndices)
{
	m_DrawCount = numOfIndices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	vector<vec3> position;
	vector<vec3> colors;

	position.reserve(numOfVertices);
	colors.reserve(numOfVertices);

	for (unsigned int i = 0; i < numOfVertices; ++i)
	{
		position.push_back(Vertices[i].GetPosition());
		colors.push_back(Vertices[i].GetColors());
	}

	glGenBuffers(TOTAL_BUFFERS, m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(position[0]), &position[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[COLORS_VB]);
	glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

// -------------------
// Author: Rony Hanna
// Description: Function that sends position, color, and texture data to the GPU 
// -------------------
void Mesh::InitGeometry(CVertex_PT* Vertices, unsigned int numOfVertices, unsigned int* indices, unsigned int numOfIndices)
{
	m_DrawCount = numOfIndices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	vector<vec3> position;
	vector<vec3> colors;
	vector<vec2> textures;

	position.reserve(numOfVertices);
	colors.reserve(numOfVertices);
	textures.reserve(numOfVertices);

	for (unsigned int i = 0; i < numOfVertices; ++i)
	{
		position.push_back(Vertices[i].GetPosition());
		colors.push_back(Vertices[i].GetColors());
		textures.push_back(Vertices[i].GetTexture());
	}

	glGenBuffers(TOTAL_BUFFERS, m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(position[0]), &position[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[COLORS_VB]);
	glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[TEXTURE_VB]);
	glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(textures[0]), &textures[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

// -------------------
// Author: Rony Hanna
// Description: Function that draws the mesh 
// -------------------
void Mesh::Draw()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_DrawCount, GL_UNSIGNED_INT, 0);
}
