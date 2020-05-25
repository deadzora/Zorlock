#pragma once
#include "GameObject.h"
#include "Zorlock/Renderer/Camera.h"

namespace Zorlock {

	class GameObject;

	class Scene : public Object
	{
	public:
		Scene();
		Scene(std::string name);
		~Scene();
		virtual void Start() override;
		virtual void Awake() override;
		virtual void Update(Timestep ts) override;
		virtual void Render() override;
		virtual void Destroy() override;
		Ref<Camera> CreateCamera();
		Ref<Camera> CreateCamera(float fovDegrees, float aspectRatio, float nearZ, float farZ);
		Ref<Camera> CreateCamera2D(float left, float right, float bottom, float top);
		Ref<Camera> MainCamera();
		void SetMainCamera(Ref<Camera> cam);
		Ref<GameObject> CreateGameObject();
		Ref<GameObject> CreateGameObject(std::string name);
		void AddGameObject(Ref<GameObject> gameobject);
		Ref<GameObject> GetGameObject(std::string name);
		void RemoveGameObject(std::string, bool single = true);
		void RemoveGameObject(Ref<GameObject> gameobject, bool single = true);
	protected:
		Ref<Camera> m_mainCamera;
		std::vector<Ref<GameObject>> m_scene_Objects;

	};


}

#define ZLSCENE Zorlock::Scene