#include "ZLpch.h"
#include "GameObject.h"


namespace Zorlock
{

	GameObject::GameObject() : Object()
	{
		transform->gameObject = Ref<GameObject>(this);
		name = "GameObject";
	}

	GameObject::GameObject(std::string name) : Object(name)
	{
		transform->gameObject = Ref<GameObject>(this);
	}

	GameObject::GameObject(Ref<Transform> parent) : Object()
	{
		transform->gameObject = Ref<GameObject>(this);
		transform->parent = parent;
		name = "GameObject";
	}

	GameObject::GameObject(std::string name, Ref<Transform> parent) : Object(name)
	{
		transform->gameObject = Ref<GameObject>(this);
		transform->parent = parent;
	}

	GameObject::~GameObject()
	{
	}



	void GameObject::Start()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Start();
		}
	}

	void GameObject::Awake()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Awake();
		}
	}

	void GameObject::Update(Timestep ts)
	{
		this->transform->UpdateTransformationMatrix();
		this->transform->UpdateDirectionVectors();
		if (this->transform->parent != nullptr)
		{
			this->transform->SetDrawMatrix(this->transform->GetTransformationMatrix() * this->transform->parent->GetTransformationMatrix());
		}
		else {
			this->transform->SetDrawMatrix(this->transform->GetTransformationMatrix());
		}
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Update(ts);
		}

		for (size_t i = 0; i < transform->children.size(); i++)
		{

		}


	}

	void GameObject::Render()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Render();
		}
	}

	void GameObject::Destroy()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Destroy();
		}
		delete this;
	}

}

