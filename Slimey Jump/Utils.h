// File Name	: Utils.h 
// Description	: Sets up Utility class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__

#include "Common.h"

#include <strstream>
#include <sstream>
#include <string>

using namespace glm;

// -------------------
// Author: Rony Hanna
// Description: Function that converts to string
// -------------------
template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

// -------------------
// Author: Rony Hanna
// Description: Function that converts to wide string
// -------------------
template<typename T>
std::wstring ToWideString(const T& _value)
{
	std::wstringstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

// -------------------
// Author: Rony Hanna
// Description: Structure that holds position coordinates and color coordinates
// -------------------
struct CVertex_P
{
	vec3 position;
	vec3 colors;

	inline vec3 GetPosition() { return position; };
	inline vec3 GetColors() { return colors; };
};

// -------------------
// Author: Rony Hanna
// Description: Structure that holds position, texture coordinates, and color coordinates
// -------------------
struct CVertex_PT
{
	vec3 position;
	vec3 colors;
	vec2 texture;

	inline vec3 GetPosition() { return position; };
	inline vec2 GetTexture() { return texture; };
	inline vec3 GetColors() { return colors; };
};

#endif // !__UTILS_H__
