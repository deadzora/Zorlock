#pragma once

namespace Zorlock {

	struct Vector2 {
		float x, y;
	};

	struct Vector3 : public Vector2 {
		float z;
	};

	struct Vector4 : public Vector3 {
		float w;
	};

}