#include "ZLpch.h"
#include "Transform.h"



namespace Zorlock
{

	Transform::Transform() 
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
	}

	void Transform::SetPosition(float x, float y, float z)
	{
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
	}

	void Transform::SetRotation(float x, float y, float z)
	{
	}

	void Transform::SetRotation(const VECTOR3 rot)
	{
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
}