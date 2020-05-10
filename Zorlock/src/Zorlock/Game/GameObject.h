#pragma once
#include "Zorlock/Game/Object.h"
#include "Zorlock/Game/Component.h"


namespace Zorlock {

	class GameObject : public Object {

	public:
		GameObject();
		template <class T>
		T* GetComponent()
		{
			for each (Component c in components)
			{
				if (std::is_same<T, c>::value)
				{
					return *c;
				}
				
			}
			return nullptr;
		}
		template <class T>
		T* CreateComponent()
		{
			if (std::is_same<T, c>::value)
			{
				T* c = new T();
				return c;
			}
			return nullptr;
		}
		~GameObject();

		void UpdateDirectionVectors();

		void Destroy();
	protected:
		std::vector<Component> components;
	
	};


}