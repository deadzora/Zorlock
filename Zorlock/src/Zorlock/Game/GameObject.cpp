#include "ZLpch.h"
#include "GameObject.h"


namespace Zorlock
{

	GameObject::GameObject() : Object()
	{
	}

	GameObject::GameObject(std::string name) : Object(name)
	{
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

