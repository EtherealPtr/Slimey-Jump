// File Name	: Camera.h 
// Description	: Sets up camera class 
// Author		: Rony Hanna
// Mail			: RonyHanna@outlook.co.nz

#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtx\transform.hpp"

class Camera
{
public:
	Camera() { /* Do Nothing */ };
	~Camera() { /* Do Nothing */ };

	void initCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_Perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_CameraPos = pos;
		m_CameraViewDir = glm::vec3(0.0f, 0.0f, -1.0f);
		m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	inline glm::mat4 GetProjectionMatrix() const { return m_Perspective; }
	inline glm::mat4 ViewMatrix() const { return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraViewDir, m_UpVector); }
	inline glm::vec3& GetCameraPosition() { return m_CameraPos; };

private:
	glm::mat4 m_Perspective;
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraViewDir;
	glm::vec3 m_UpVector;
};

#endif // !__CAMERA_H__