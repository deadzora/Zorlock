#include "ZLpch.h"
#include "Zorlock/Renderer/OrthographicCamera.h"


namespace Zorlock {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	{
		ZL_PROFILE_FUNCTION();


		projectionMatrix.makeProjectionOrtho(left, right, top, bottom, -1.0f, 1.0f);
		viewMatrix.SetInverseTransRotScale(this->transform->position, QUATERNION::EulerAngles(Vector3(0, 0, DEGREES_FROM_RADIANS(m_Rotation))), VECTOR3(1, 1, 1));

	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		ZL_PROFILE_FUNCTION();

		projectionMatrix.makeProjectionOrtho(left, right, top, bottom, -1.0f, 1.0f);
		viewMatrix.SetInverseTransRotScale(this->transform->position, QUATERNION::EulerAngles(Vector3(0, 0, DEGREES_FROM_RADIANS(m_Rotation))), VECTOR3(1, 1, 1));

	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		ZL_PROFILE_FUNCTION();
		UpdateViewMatrix();

	}

	void OrthographicCamera::UpdateViewMatrix()
	{

		viewMatrix.SetInverseTransRotScale(this->transform->position, QUATERNION::EulerAngles(Vector3(0, 0, DEGREES_FROM_RADIANS(m_Rotation))), VECTOR3(1, 1, 1));
		this->transform->UpdateDirectionVectors();
	}

}