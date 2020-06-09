#pragma once
#include "Zorlock\Core\Timestep.h"

namespace Zorlock {

	class GameObject;

	class Component {
	public:
		~Component() = default;
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update(Timestep ts) = 0;
		virtual void Render() = 0;
		virtual void Destroy() = 0;
		void SetParent(Ref<GameObject> go)
		{
			parent = go;
		}
		void SetName(std::string n)
		{
			name = n;
		}
		std::string GetType()
		{
			return type;
		}
		std::string name;
		Ref<GameObject> parent;
	protected:
		std::string type;
	};

	ZL_ENABLE_TYPENAME(Component)
}

#define ZLCOMPONENT Zorlock::Component