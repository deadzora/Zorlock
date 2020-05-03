#include "Object3D.h"
#include "GameObject.h"


Object3D::Object3D()
{
}


Object3D::~Object3D()
{
}


const XMVECTOR & Object3D::GetFowardVector(bool omitY)
{
	if (omitY)
	{
		return this->vec_forward_noY;
	}
	else {
		return this->vec_forward;
	}

}

const XMVECTOR & Object3D::GetRightVector(bool omitY)
{
	if (omitY)
	{
		return this->vec_right_noY;
	}
	else {
		return this->vec_right;
	}

}

const XMVECTOR & Object3D::GetLeftVector(bool omitY)
{
	if (omitY)
	{
		return this->vec_left_noY;
	}
	else {
		return this->vec_left;
	}

}

const XMVECTOR & Object3D::GetBackVector(bool omitY)
{
	if (omitY)
	{
		return this->vec_back_noY;
	}
	else {
		return this->vec_back;
	}

}

void Object3D::UpdateDirectionVectors()
{
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, 0.0f);

	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_back = XMVector3TransformCoord(this->DEFAULT_BACK_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);

	XMMATRIX vecRotationMatrix_noY = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);

	this->vec_forward_noY = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix_noY);
	this->vec_back_noY = XMVector3TransformCoord(this->DEFAULT_BACK_VECTOR, vecRotationMatrix_noY);
	this->vec_left_noY = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix_noY);
	this->vec_right_noY = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix_noY);

}


