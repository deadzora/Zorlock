#include "ZLpch.h"
#include "Transform.h"



namespace Zorlock
{

	Transform::Transform() : position(VECTOR3()), rotation(QUATERNION::IDENTITY()), scale(VECTOR2(1,1))
	{
	}
	Transform::~Transform()
	{
	}
	VECTOR3 Transform::GetPosition()
	{
		return VECTOR3();
	}
	void Transform::SetPosition(const VECTOR3& pos)
	{
		position = pos;
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void Transform::AdjustPosition(const VECTOR3& pos)
	{
	}

	void Transform::AdjustPosition(float x, float y, float z)
	{
	}

	QUATERNION Transform::GetRotation()
	{
		return QUATERNION();
	}

	void Transform::SetRotation(const VECTOR3& rot)
	{
		rotation = QUATERNION::EulerAngles(rot);
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		rotation = QUATERNION::EulerAngles(VECTOR3(x,y,z));
	}

	void Transform::SetRotation(const VECTOR3 rot)
	{
		rotation = QUATERNION::EulerAngles(rot);
	}

	void Transform::AdjustRotation(const VECTOR3& rot)
	{
	}

	void Transform::AdjustRotation(float x, float y, float z)
	{
	}

	void Transform::SetScale(const VECTOR3& pos)
	{
	}

	void Transform::SetScale(float x, float y, float z)
	{
	}

	void Transform::AdjustScale(const VECTOR3& pos)
	{
	}

	void Transform::AdjustScale(float x, float y, float z)
	{
	}
	void Transform::UpdateDirectionVectors()
	{
		MATRIX4 vecRotationMatrix = MATRIX4::IDENTITY().toRotationMatrix(Quaternion().FromEulerAngles(VECTOR3(this->rotation.ToEulerAngles().x, this->rotation.ToEulerAngles().y,0.0f)));

		this->vec_forward = vecRotationMatrix * this->DEFAULT_FORWARD_VECTOR;
		this->vec_back = vecRotationMatrix * this->DEFAULT_BACK_VECTOR;
		this->vec_left = vecRotationMatrix * this->DEFAULT_LEFT_VECTOR;
		this->vec_right = vecRotationMatrix * this->DEFAULT_RIGHT_VECTOR;

		MATRIX4 vecRotationMatrix_noY = MATRIX4::IDENTITY().toRotationMatrix(Quaternion().FromEulerAngles(VECTOR3(0.0f, this->rotation.ToEulerAngles().y, 0.0f)));

		this->vec_forward_noY = vecRotationMatrix_noY * this->DEFAULT_FORWARD_VECTOR;
		this->vec_back_noY = vecRotationMatrix_noY * this->DEFAULT_BACK_VECTOR;
		this->vec_left_noY = vecRotationMatrix_noY * this->DEFAULT_LEFT_VECTOR;
		this->vec_right_noY = vecRotationMatrix_noY * this->DEFAULT_RIGHT_VECTOR;


	}
	const VECTOR4& Transform::GetFowardVector(bool omitY)
	{
		if (omitY)
		{
			return this->vec_forward_noY;
		}
		else {
			return this->vec_forward;
		}
	}
	const VECTOR4& Transform::GetRightVector(bool omitY)
	{
		if (omitY)
		{
			return this->vec_right_noY;
		}
		else {
			return this->vec_right;
		}
	}
	const VECTOR4& Transform::GetLeftVector(bool omitY)
	{
		if (omitY)
		{
			return this->vec_left_noY;
		}
		else {
			return this->vec_left;
		}
	}
	const VECTOR4& Transform::GetBackVector(bool omitY)
	{
		if (omitY)
		{
			return this->vec_back_noY;
		}
		else {
			return this->vec_back;
		}
	}
}