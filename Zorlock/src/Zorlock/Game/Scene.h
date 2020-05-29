#pragma once
#include "GameObject.h"
#include "Zorlock/Renderer/Light.h"

namespace Zorlock {

	class Environment;
	class Camera;
	class OrthographicCamera;


	enum class LightType;

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
		Ref<Camera> CreateCamera(std::string name="Camera");
		Ref<Camera> CreateCamera(float fovDegrees, float aspectRatio, float nearZ, float farZ, std::string name = "Camera");
		Ref<OrthographicCamera> CreateCamera2D(float left, float right, float bottom, float top, std::string name = "OrthoCamera");
		Ref<Camera> MainCamera();
		void SetMainCamera(Ref<Camera> cam);
		Ref<GameObject> CreateGameObject(std::string name = "GameObject");
		void AddGameObject(Ref<GameObject> gameobject);
		Ref<GameObject> GetGameObject(std::string name);
		void RemoveGameObject(std::string, bool single = true);
		void RemoveGameObject(Ref<GameObject> gameobject, bool single = true);
		Ref<Light> CreateLight();
		Ref<Light> CreateLight(LightType light);
		Ref<Environment> GetEnvironment();
	protected:
		Ref<Camera> m_mainCamera;
		Ref<Environment> m_environment;
		std::vector<Ref<GameObject>> m_scene_Objects;
		std::vector<Ref<Light>> m_scene_Lights;
	};


}

#define ZLSCENE Zorlock::Scene