#pragma once
#include "Scene.h"



namespace Zorlock
{

	class SceneManager
	{
	public:
		SceneManager();
		void SetCurrentScene(Ref<Scene> scene);
		bool SetCurrentScene(std::string name);
		void AddScene(Ref<Scene> scene);
		Ref<Scene> CreateScene(std::string name);
		Ref<Scene> GetScene(std::string name);
		Ref<Scene> GetActiveScene();
		static Ref<SceneManager> GetInstance();
	private:
		Ref<Scene> m_activeScene;
		std::vector<Ref<Scene>> m_scenes;
	};
}
#define ZLSCENEMANAGER Zorlock::SceneManager
#define ZLSCREATESCENE(name) Zorlock::SceneManager::GetInstance()->CreateScene(name);
#define ZLCREATECAMERA(fov,ar,n,f) Zorlock::SceneManager::GetInstance()->GetActiveScene()->CreateCamera(fov,ar,n,f);
#define ZLCREATECAMERA2D(l,r,b,t) Zorlock::SceneManager::GetInstance()->GetActiveScene()->CreateCamera(l,r,b,t);

