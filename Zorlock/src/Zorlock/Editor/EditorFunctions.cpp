#include "ZLpch.h"
#include "EditorFunctions.h"
#include "Zorlock/Game/SceneManager.h"
#include "Zorlock/Game/GameObject.h"
#include "Zorlock/Renderer/Material.h"
#include "Zorlock/Components/MeshRenderer.h"
#include "Zorlock/Renderer/Texture.h"
#include "Zorlock/Renderer/Light.h"
namespace Zorlock
{

	void EditorFunctions::CreateCube(std::string name, Ref<Transform> parent)
	{
		GameObject* go = nullptr;
		if (parent != nullptr)
		{
			go = new GameObject(name, parent);
		}
		else {
			go = SceneManager::GetInstance()->GetActiveScene()->CreateGameObject(name).get();
		}
		if (go != nullptr)
		{
			MeshRenderer* mr = go->CreateComponent<MeshRenderer>().get();
			mr->CreateCube();
			Material* m = mr->GetMaterial(0).get();
			//Ref<Texture2D> t = Texture2D::Create(1, 1, 0xffffffff);
			m->LoadTexture(1, 1, 0xffffffff);
		}
	}

	void EditorFunctions::CreateCone(std::string name, Ref<Transform> parent)
	{
		GameObject* go = nullptr;
		if (parent != nullptr)
		{
			go = new GameObject(name, parent);
		}
		else {
			go = SceneManager::GetInstance()->GetActiveScene()->CreateGameObject(name).get();
		}
		if (go != nullptr)
		{
			MeshRenderer* mr = go->CreateComponent<MeshRenderer>().get();
			mr->CreateCone(16);
			Material* m = mr->GetMaterial(0).get();
			//Ref<Texture2D> t = Texture2D::Create(1, 1, 0xffffffff);
			m->LoadTexture(1, 1, 0xffffffff);
		}
	}

	void EditorFunctions::CreateSphere(std::string name, Ref<Transform> parent)
	{
		GameObject* go = nullptr;
		if (parent != nullptr)
		{
			go = new GameObject(name, parent);
		}
		else {
			go = SceneManager::GetInstance()->GetActiveScene()->CreateGameObject(name).get();
		}
		if (go != nullptr)
		{
			MeshRenderer* mr = go->CreateComponent<MeshRenderer>().get();
			mr->CreateSphere(16);
			Material* m = mr->GetMaterial(0).get();
			//Ref<Texture2D> t = Texture2D::Create(1, 1, 0xffffffff);
			m->LoadTexture(1, 1, 0xffffffff);
		}
	}

	void EditorFunctions::CreateCylinder(std::string name, Ref<Transform> parent)
	{
		GameObject* go = nullptr;
		if (parent != nullptr)
		{
			go = new GameObject(name, parent);
		}
		else {
			go = SceneManager::GetInstance()->GetActiveScene()->CreateGameObject(name).get();
		}
		if (go != nullptr)
		{
			MeshRenderer* mr = go->CreateComponent<MeshRenderer>().get();
			mr->CreateCylinder(16);
			Material* m = mr->GetMaterial(0).get();
			//Ref<Texture2D> t = Texture2D::Create(1, 1, 0xffffffff);
			m->LoadTexture(1, 1, 0xffffffff);
		}
	}

	void EditorFunctions::CreateQuad(std::string name, Ref<Transform> parent)
	{
		GameObject* go = nullptr;
		if (parent != nullptr)
		{
			go = new GameObject(name, parent);
		}
		else {
			go = SceneManager::GetInstance()->GetActiveScene()->CreateGameObject(name).get();
		}
		if (go != nullptr)
		{
			MeshRenderer* mr = go->CreateComponent<MeshRenderer>().get();
			mr->CreateQuad();
			Material* m = mr->GetMaterial(0).get();
			//Ref<Texture2D> t = Texture2D::Create(1, 1, 0xffffffff);
			m->LoadTexture(1, 1, 0xffffffff);
		}
	}

	void EditorFunctions::CreateLight(std::string name, Ref<Transform> parent)
	{
		Light* go = nullptr;
		if (parent != nullptr)
		{
			go = new Light(name, parent);
		}
		else {
			go = SceneManager::GetInstance()->GetActiveScene()->CreateLight(LightType::POINTLIGHT).get();
		}
		if (go != nullptr)
		{
			go->name = name;
		}
	}


}
