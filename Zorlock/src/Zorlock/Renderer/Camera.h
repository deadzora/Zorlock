#pragma once
#include "Zorlock/Game/GameObject.h"

namespace Zorlock {


	class Camera : GameObject
	{
		Camera();
		void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
		const MATRIX4& GetViewMatrix() const;
		const MATRIX4& GetProjectionMatrix() const;
		void SetLookAtPos(VECTOR3 lookAtPos);
		~Camera();

	private:
		void UpdateViewMatrix();
		MATRIX4 viewMatrix;
		MATRIX4 projectionMatrix;

	};


}