#pragma once
#include "Zorlock/Renderer/Camera.h"
#include <glm/glm.hpp>

namespace Zorlock {

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(std::string name = "OrthodCamera", Ref<Transform> parent = nullptr);
		OrthographicCamera(float left, float right, float bottom, float top, std::string name = "OrthoCamera", Ref<Transform> parent = nullptr);

		void SetProjection(float left, float right, float bottom, float top);
		ZL_DEPRECATED("No need to get position on camera anymore, handled by inhereted transform")
		const VECTOR3 GetPosition() const { return transform->GetPosition(); }
		ZL_DEPRECATED("No need to set position on camera anymore, handled by inhereted transform")
		void SetPosition(const VECTOR3& position) { transform->SetPosition(position); RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		virtual void UpdateViewMatrix() override;
	private:
		void RecalculateViewMatrix();

	private:
		float m_Rotation;
	};

}

#define ZLORTHOCAM Zorlock::OrthographicCamera
