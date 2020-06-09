#include "ZLpch.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

namespace Zorlock {

	Camera::Camera(std::string name, Ref<Transform> parent) : GameObject(name, parent), viewMatrix(MATRIX4::IDENTITY()), projectionMatrix(MATRIX4::IDENTITY()), m_Fov(0), m_aspectRatio(0), m_nearZ(0), m_farZ(1)
	{
		type = ZL_GETTYPENAME(Camera)
	}
	Camera::Camera(float fovDegrees, float aspectRatio, float nearZ, float farZ, std::string name, Ref<Transform> parent) : GameObject(name,parent), m_Fov(fovDegrees), m_aspectRatio(aspectRatio), m_nearZ(nearZ), m_farZ(farZ)
	{
		name = "Camera";
		SetProjectionValues(fovDegrees, aspectRatio, nearZ, farZ);
		type = ZL_GETTYPENAME(Camera)
	}
	Camera::Camera(MATRIX4 proj, MATRIX4 view, std::string name, Ref<Transform> parent) : GameObject(name, parent), viewMatrix(view), projectionMatrix(proj), m_Fov(0), m_aspectRatio(0), m_nearZ(0), m_farZ(1)
	{
		type = ZL_GETTYPENAME(Camera)
	}
	void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
	{
		float fovRadians = RADIANS_FROM_DEGREES(fovDegrees);
		projectionMatrix = MATRIX4::projectionPerspective(fovRadians, aspectRatio, nearZ, farZ);
		UpdateViewMatrix();
	}

	void Camera::UpdateProjectionValues()
	{
		float fovRadians = RADIANS_FROM_DEGREES(m_Fov);
		projectionMatrix = MATRIX4::projectionPerspective(fovRadians, m_aspectRatio, m_nearZ, m_farZ);
		UpdateViewMatrix();
	}

	

	void Camera::SetLookAtPos(VECTOR3 lookAtPos)
	{
		if (lookAtPos.x == this->transform->position.x && lookAtPos.y == this->transform->position.y && lookAtPos.z == this->transform->position.z)
		{
			return;
		}
		lookAtPos.x = this->transform->position.x - lookAtPos.x;
		lookAtPos.y = this->transform->position.y - lookAtPos.y;
		lookAtPos.z = this->transform->position.z - lookAtPos.z;

		float pitch = 0.0f;
		if (lookAtPos.y != 0.0f)
		{
			const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
			pitch = atan(lookAtPos.y / distance);
		}

		float yaw = 0.0f;
		if (lookAtPos.x != 0.0f)
		{
			yaw = atan(lookAtPos.x / lookAtPos.z);
		}
		if (lookAtPos.z > 0)
		{
			yaw += M_PI;
		}

		this->transform->SetRotation(pitch, yaw, 0.0f);

	}

	VECTOR4 Camera::GetCamPosition()
	{
		return VECTOR4(transform->GetDrawMatrix() * transform->position,1.0f);
	}

	Camera::~Camera()
	{
	}

	void  Camera::Update(Timestep ts)
	{
		GameObject::Update(ts);
		UpdateViewMatrix();
	}

	void Camera::UpdateViewMatrix()
	{
		//SetLookAtPos(Vector3(0, 0, 0));
		viewMatrix.SetInverseTransRotScale(this->transform->position, this->transform->rotation, VECTOR3(1, 1, 1));
		this->transform->UpdateDirectionVectors();

	}

}

