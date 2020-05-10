#pragma once
#include "Zorlock/Core/Math.h"
#define TRANSFORM Zorlock::Transform

namespace Zorlock {

	//class GameObject;

	class Transform : public MathTransform
	{
	public:
		Transform();
		~Transform();
		
		Transform * parent;
		VECTOR3 position;
		QUATERNION rotation;
		VECTOR3 scale;
		virtual VECTOR3 GetPosition();
		virtual void SetPosition(const VECTOR3& pos);
		virtual void SetPosition(float x, float y, float z);
		virtual void AdjustPosition(const VECTOR3& pos);
		virtual void AdjustPosition(float x, float y, float z);
		virtual QUATERNION GetRotation();
		virtual void SetRotation(const VECTOR3& rot);
		virtual void SetRotation(float x, float y, float z);
		virtual void SetRotation(const VECTOR3 rot);
		virtual void AdjustRotation(const VECTOR3& rot);
		virtual void AdjustRotation(float x, float y, float z);
		virtual void SetScale(const VECTOR3& pos);
		virtual void SetScale(float x, float y, float z);
		virtual void AdjustScale(const VECTOR3& pos);
		virtual void AdjustScale(float x, float y, float z);

	};


}
