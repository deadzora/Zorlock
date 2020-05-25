#include "ZLpch.h"
#include "Camera.h"




namespace Zorlock {
	Camera::Camera() : viewMatrix(MATRIX4::IDENTITY()), projectionMatrix(MATRIX4::IDENTITY())
	{

	}
	Camera::Camera(float fovDegrees, float aspectRatio, float nearZ, float farZ)
	{
		SetProjectionValues(fovDegrees, aspectRatio, nearZ, farZ);
	}
	Camera::Camera(MATRIX4 proj, MATRIX4 view) : viewMatrix(view), projectionMatrix(proj)
	{
		
	}
	void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
	{
		float fovRadians = RADIANS_FROM_DEGREES(fovDegrees);
		projectionMatrix = MATRIX4::projectionPerspective(fovRadians, aspectRatio, nearZ, farZ);
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

	Zorlock::Camera::~Camera()
	{
	}

	void Zorlock::Camera::UpdateViewMatrix()
	{
		viewMatrix.SetInverseTransRotScale(this->transform->position, this->transform->rotation, VECTOR3(1, 1, 1));

		this->transform->UpdateDirectionVectors();

	}
}

