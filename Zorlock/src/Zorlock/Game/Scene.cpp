#include "ZLpch.h"
#include "Scene.h"
#include "Zorlock/Renderer/OrthographicCamera.h"
#include "Zorlock/Renderer/Environment.h"
#include "Zorlock/Renderer/Light.h"

namespace Zorlock
{
	Scene::Scene() : Object("Scene"), m_environment(Ref<Environment>(new Environment()))
	{
	}

	Scene::Scene(std::string name) : Object(name), m_environment(Ref<Environment>(new Environment()))
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Start()
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			m_scene_Objects[i]->Start();
		}
	}

	void Scene::Awake()
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			m_scene_Objects[i]->Awake();
		}
	}

	void Scene::Update(Timestep ts)
	{
		transform->UpdateTransformationMatrix();
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			m_scene_Objects[i]->Update(ts);
		}
	}

	void Scene::Render()
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			m_scene_Objects[i]->Render();
		}
	}

	void Scene::Destroy()
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			m_scene_Objects[i]->Destroy();
		}

		delete this;
	}

	Ref<Camera> Scene::CreateCamera(std::string name)
	{
		if (m_mainCamera == nullptr)
		{
			m_mainCamera = CreateRef<Camera>(name,this->transform);
			m_scene_Objects.push_back(m_mainCamera);
			return m_mainCamera;
		}
		else {
			Ref<Camera> c = CreateRef<Camera>(name, this->transform);
			m_scene_Objects.push_back(c);
			return c;
		}
	}

	Ref<Camera> Scene::CreateCamera(float fovDegrees, float aspectRatio, float nearZ, float farZ, std::string name)
	{
		if (m_mainCamera == nullptr)
		{
			m_mainCamera = CreateRef<Camera>(fovDegrees, aspectRatio, nearZ, farZ, name, this->transform);
			m_scene_Objects.push_back(m_mainCamera);
			return m_mainCamera;
		}
		else {
			Ref<Camera> c = CreateRef<Camera>(fovDegrees, aspectRatio, nearZ, farZ, name, this->transform);
			m_scene_Objects.push_back(c);
			return c;
		}

	}

	Ref<OrthographicCamera> Scene::CreateCamera2D(float left, float right, float bottom, float top, std::string name)
	{
		if (m_mainCamera == nullptr)
		{
			Ref<OrthographicCamera> c = CreateRef<OrthographicCamera>(left, right, bottom, top, name, this->transform);
			m_scene_Objects.push_back(c);
			m_mainCamera = c;
			return c;
		}
		else {
			Ref<OrthographicCamera> c = CreateRef<OrthographicCamera>(left, right, bottom, top, name, this->transform);
			m_scene_Objects.push_back(c);
			return c;
		}

	}

	Ref<Camera> Scene::MainCamera()
	{
		return m_mainCamera;
	}

	void Scene::SetMainCamera(Ref<Camera> cam)
	{
		m_mainCamera = cam;
	}


	Ref<GameObject> Scene::CreateGameObject(std::string name)
	{
		Ref<GameObject> go = CreateRef<GameObject>(name, this->transform);
		m_scene_Objects.push_back(go);
		return go;
	}

	void Scene::AddGameObject(Ref<GameObject> gameobject)
	{
		m_scene_Objects.push_back(gameobject);
	}

	Ref<GameObject> Scene::GetGameObject(std::string name)
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			if (m_scene_Objects[i]->name.compare(name) == 0)
			{
				return m_scene_Objects[i];
			}
		}

		return nullptr;
	}

	void Scene::RemoveGameObject(std::string, bool single)
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			if (m_scene_Objects[i]->name.compare(name) == 0)
			{
				m_scene_Objects.erase(m_scene_Objects.begin() + i);
				m_scene_Objects.shrink_to_fit();
				if(single) return;
			}
		}
	}

	void Scene::RemoveGameObject(Ref<GameObject> gameobject, bool single)
	{
		for (size_t i = 0; i < m_scene_Objects.size(); i++)
		{
			if (m_scene_Objects[i] == gameobject)
			{
				m_scene_Objects.erase(m_scene_Objects.begin() + i);
				m_scene_Objects.shrink_to_fit();
				if (single) return;
			}
		}
	}

	Ref<Light> Scene::CreateLight()
	{
		Ref<Light> go = CreateRef<Light>(name, this->transform);
		m_scene_Objects.push_back(go);
		m_scene_Lights.push_back(go);
		return go;
	}

	Ref<Light> Scene::CreateLight(LightType light)
	{
		//not implmented other lighttypes for now just create point light
		Ref<Light> go = CreateRef<Light>(name, this->transform);
		m_scene_Objects.push_back(go);
		m_scene_Lights.push_back(go);
		return go;
	}

	Ref<Environment> Scene::GetEnvironment()
	{
		return m_environment;
	}




}