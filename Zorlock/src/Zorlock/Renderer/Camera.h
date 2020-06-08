#pragma once
#include "Zorlock/Game/GameObject.h"
#include <queue>

namespace Zorlock {



	class Camera : public GameObject
	{
	public:
		Camera(std::string name = "Camera", Ref<Transform> parent = nullptr);
		Camera(float fovDegrees, float aspectRatio, float nearZ, float farZ,std::string name = "Camera", Ref<Transform> parent = nullptr);
		Camera(MATRIX4 view, MATRIX4 proj, std::string name = "Camera", Ref<Transform> parent = nullptr);
		void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
		const MATRIX4 GetProjectionMatrix() const { return projectionMatrix; }
		const MATRIX4 GetViewMatrix() const { return viewMatrix; }
		const MATRIX4 GetViewProjectionMatrix() const 
		{ 
			return projectionMatrix * viewMatrix;
			//return MATRIX4::IDENTITY();
		}
		void SetLookAtPos(VECTOR3 lookAtPos);
		virtual VECTOR4 GetCamPosition();
		virtual void Update(Timestep ts) override;
		virtual void UpdateViewMatrix();

		~Camera();

	protected:

		MATRIX4 viewMatrix;
		MATRIX4 projectionMatrix;

	};

	ZL_ENABLE_TYPENAME(Camera)
}

#define ZLCAMERA Zorlock::Camera