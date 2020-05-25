#pragma once
#include "Zorlock\Game\Transform.h"
#include "Zorlock\Core\Timestep.h"

namespace Zorlock {

	class Object {
	public:
		Object();
		Object(std::string name);
		~Object();
		virtual void Start() = 0;
		virtual void Awake() = 0;
		virtual void Update(ZLTIME ts) = 0;
		virtual void Render() = 0;
		virtual void Destroy() = 0;
		std::string name;
		ZLREF<TRANSFORM> transform;
	};

}

#define ZLOBJECT Zorlock::Object