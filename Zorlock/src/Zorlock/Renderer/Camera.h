#pragma once
#include "Zorlock/Game/GameObject.h"

namespace Zorlock {


	class Camera : public GameObject
	{
	public:
		Camera();
		Camera(float fovDegrees, float aspectRatio, float nearZ, float farZ);
		Camera(MATRIX4 view, MATRIX4 proj);
		void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
		const MATRIX4 GetProjectionMatrix() const { return projectionMatrix; }
		const MATRIX4 GetViewMatrix() const { return viewMatrix; }
		const MATRIX4 GetViewProjectionMatrix() const 
		{ 
			return projectionMatrix * viewMatrix;
			//return MATRIX4::IDENTITY();
		}
		void SetLookAtPos(VECTOR3 lookAtPos);
		virtual void UpdateViewMatrix();
		~Camera();

	protected:
		
		MATRIX4 viewMatrix;
		MATRIX4 projectionMatrix;

	};


}

#define ZLCAMERA Zorlock::Camera