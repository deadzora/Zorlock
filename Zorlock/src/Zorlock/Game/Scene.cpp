#include "ZLpch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Zorlock/Renderer/OrthographicCamera.h"

namespace Zorlock
{
	Scene::Scene() : Object()
	{
	}

	Scene::Scene(std::string name) : Object(name)
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

	Ref<Camera> Scene::CreateCamera()
	{
		m_mainCamera = CreateRef<Camera>();

		m_scene_Objects.push_back(m_mainCamera);
		return m_mainCamera;
	}

	Ref<Camera> Scene::CreateCamera(float fovDegrees, float aspectRatio, float nearZ, float farZ)
	{
		m_mainCamera = CreateRef<Camera>(fovDegrees,aspectRatio,nearZ,farZ);
		m_scene_Objects.push_back(m_mainCamera);
		return m_mainCamera;
	}

	Ref<Camera> Scene::CreateCamera2D(float left, float right, float bottom, float top)
	{
		m_mainCamera = CreateRef<OrthographicCamera>(left,right,bottom,top);
		m_scene_Objects.push_back(m_mainCamera);
		return m_mainCamera;
	}

	Ref<Camera> Scene::MainCamera()
	{
		return m_mainCamera;
	}

	void Scene::SetMainCamera(Ref<Camera> cam)
	{
		m_mainCamera = cam;
	}

	Ref<GameObject> Scene::CreateGameObject()
	{
		Ref<GameObject> go = CreateRef<GameObject>();
		m_scene_Objects.push_back(go);
		return go;
	}

	Ref<GameObject> Scene::CreateGameObject(std::string name)
	{
		Ref<GameObject> go = CreateRef<GameObject>(name);
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




}