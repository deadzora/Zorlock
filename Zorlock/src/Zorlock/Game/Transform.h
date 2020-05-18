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
	protected:
		virtual void UpdateDirectionVectors();
		const VECTOR4& GetFowardVector(bool omitY = false);
		const VECTOR4& GetRightVector(bool omitY = false);
		const VECTOR4& GetLeftVector(bool omitY = false);
		const VECTOR4& GetBackVector(bool omitY = false);
		const VECTOR4 DEFAULT_FORWARD_VECTOR = VECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
		const VECTOR4 DEFAULT_UP_VECTOR = VECTOR4(0.0f, 1.0f, 0.0f, 0.0f);
		const VECTOR4 DEFAULT_BACK_VECTOR = VECTOR4(0.0f, 0.0f, -1.0f, 0.0f);
		const VECTOR4 DEFAULT_LEFT_VECTOR = VECTOR4(-1.0f, 0.0f, 0.0f, 0.0f);
		const VECTOR4 DEFAULT_RIGHT_VECTOR = VECTOR4(1.0f, 0.0f, 0.0f, 0.0f);
		const VECTOR4 DEFAULT_DOWN_VECTOR = VECTOR4(0.0f, -1.0f, 0.0f, 0.0f);

		VECTOR4 vec_forward;
		VECTOR4 vec_left;
		VECTOR4 vec_right;
		VECTOR4 vec_back;

		VECTOR4 vec_forward_noY;
		VECTOR4 vec_left_noY;
		VECTOR4 vec_right_noY;
		VECTOR4 vec_back_noY;
	};


}
