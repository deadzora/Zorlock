#pragma once
#include "Zorlock/Core/Math.h"


namespace Zorlock {

	class GameObject;

	class Transform : public MathTransform
	{
	public:
		Transform();
		~Transform();
		
		ZLREF<Transform> parent;
		ZLREF<GameObject> gameObject;
		std::vector<Ref<Transform>> children;
		VECTOR3 position;
		QUATERNION rotation;
		VECTOR3 scale;
		void AddChild(ZLREF<Transform> child);
		void RemoveChild(ZLREF<Transform> child);
		std::vector<Ref<Transform>>& GetChildren()
		{
			return children;
		}
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
		void SetMatrix(MATRIX4 matrix);
		virtual void SetDrawMatrix(MATRIX4 matrix);
		virtual MATRIX4 GetDrawMatrix();
		virtual MATRIX4 GetTransformationMatrix();
		virtual void UpdateDirectionVectors();
		virtual void UpdateTransformationMatrix();
	protected:
		
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
		MATRIX4 draw_transformation;
		MATRIX4 transformation;
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
#define TRANSFORM Zorlock::Transform