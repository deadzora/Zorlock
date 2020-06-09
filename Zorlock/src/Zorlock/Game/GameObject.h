#pragma once
#include "Zorlock/Game/Object.h"
#include "Zorlock/Game/Component.h"


namespace Zorlock {

	class GameObject : public Object {

	public:
		GameObject();
		GameObject(std::string name);
		GameObject(Ref<Transform> parent);
		GameObject(std::string name, Ref<Transform> parent);

		template <class T>
		Ref<T> GetComponent()
		{
			if (std::is_convertible<T*, Component*>::value)
			{
				for each (Ref<Component> c in components)
				{
					if (std::is_same<Ref<T>, typeid(c)>::value)
					{
						return c;
					}
				}
			}
			return nullptr;
		}

		template <class T>
		Ref<T> CreateComponent()
		{
			if (std::is_convertible<T*, Component*>::value)
			{
				Ref<T> c = CreateRef<T>();
				Ref<Component> a = c;
				a->SetParent(Ref<GameObject>(this));
				components.push_back(c);
				return c;
			}
			return nullptr;
		}

		template <class T>
		void AddComponent(Ref<T> c)
		{
			if (std::is_convertible<T*, Component*>::value)
			{
				components.push_back(c);
			}
		}
		template <class T>
		void RemoveComponent()
		{
			uint32_t index = 0;
			for each (Ref<Component> c in components)
			{
				if (std::is_convertible<T*, Component*>::value)
				{
					if (std::is_same<Ref<T>, typeid(c)>::value)
					{
						components.erase(components.begin() + index);
						components.shrink_to_fit();
						return;
					}
				}
				index++;
			}
		}
		template <class T>
		void RemoveComponents()
		{
			uint32_t index = 0;
			for each (Ref<Component> c in components)
			{
				if (std::is_convertible<T*, Component*>::value)
				{
					if (std::is_same<Ref<T>, typeid(c)>::value)
					{
						components.erase(components.begin() + index);
						components.shrink_to_fit();
						
					}
				}
				index++;
			}
		}

		~GameObject();

		virtual void Start() override;
		virtual void Awake() override;
		virtual void Update(Timestep ts) override;
		virtual void Render() override;
		virtual void Destroy() override;
		std::string GetType()
		{
			return type;
		}
		std::vector<Ref<Component>>& GetComponents()
		{
			return components;
		}
		
	protected:
		std::string type;
		std::vector<Ref<Component>> components;
	};

	ZL_ENABLE_TYPENAME(GameObject)
}

#define ZLGAMEOBJECT Zorlock::GameObject
