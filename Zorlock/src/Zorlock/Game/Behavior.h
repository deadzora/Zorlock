#pragma once
#include "Component.h"

namespace Zorlock {

	class Behavior : public Component {
	public:
		virtual ~Behavior() = default;
		virtual void Awake() const = 0;
		virtual void Start() const = 0;
		virtual void Update() const = 0;
		virtual void Destroy() const = 0;
	};

}