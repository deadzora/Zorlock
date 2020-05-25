#include "ZLpch.h"
#include "SceneManager.h"

namespace Zorlock
{
	SceneManager sceneManager;
	Ref<SceneManager> m_sceneManager;
	
	SceneManager::SceneManager()
	{
		
	}

	void SceneManager::SetCurrentScene(Ref<Scene> scene)
	{
		m_activeScene = scene;
		bool inlist = false;
		for (size_t i = 0; i < m_scenes.size(); i++)
		{
			if (m_scenes[i] == scene)
			{
				inlist = true;
				break;
			}
		}
		if (!inlist) m_scenes.push_back(scene);

	}

	bool SceneManager::SetCurrentScene(std::string name)
	{
		for (size_t i = 0; i < m_scenes.size(); i++)
		{
			if (m_scenes[i]->name.compare(name) == 0)
			{
				m_activeScene = m_scenes[i];
				return true;
			}
		}

		return false;
	}

	void SceneManager::AddScene(Ref<Scene> scene)
	{
		m_scenes.push_back(scene);
	}

	Ref<Scene> SceneManager::CreateScene(std::string name)
	{
		Ref<Scene> scene = CreateRef<Scene>(name);
		m_scenes.push_back(scene);
		m_activeScene = scene;
		return scene;
	}

	Ref<Scene> SceneManager::GetScene(std::string name)
	{
		for (size_t i = 0; i < m_scenes.size(); i++)
		{
			if (m_scenes[i]->name.compare(name) == 0)
			{
				return m_scenes[i];
			}
		}

		return nullptr;
	}

	ZLREF<Scene> SceneManager::GetActiveScene()
	{
		return m_activeScene;
	}

	Ref<SceneManager> SceneManager::GetInstance()
	{
		if (m_sceneManager == nullptr)
		{
			m_sceneManager = CreateRef<SceneManager>(sceneManager);
		}

		return m_sceneManager;
	}



}
