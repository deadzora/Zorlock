#include "OrthoCamera.h"



OrthoCamera::OrthoCamera()
{
	this->pos = XMFLOAT3(0, 0, 0);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0, 0, 0);
	this->rotVector = XMLoadFloat3(&rot);
	this->UpdateMatrix();
}


OrthoCamera::~OrthoCamera()
{
}

void OrthoCamera::SetProjectionValues(float width, float height, float nearZ, float farZ)
{
	this->orthoMatrix = XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
	this->UpdateMatrix();
}

const XMMATRIX & OrthoCamera::GetOrthoMatrix() const
{
	return this->orthoMatrix;
}

const XMMATRIX & OrthoCamera::GetWorldMatrix() const
{
	return this->m_world;
}

void OrthoCamera::UpdateMatrix()
{
	XMMATRIX translationOffsetMatrix = XMMatrixTranslation(-this->pos.x,-this->pos.y, 0.0f);
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	this->m_world = camRotationMatrix * translationOffsetMatrix;
}
