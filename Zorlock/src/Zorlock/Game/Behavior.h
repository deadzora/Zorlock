#pragma once
#include "Component.h"

namespace Zorlock {

	class Behavior : Component {
		virtual ~Behavior() = default;
		virtual void Awake() const = 0;
		virtual void Start() const = 0;
		virtual void Update(void* i) = 0;
		virtual void Destroy() const = 0;

	};

}