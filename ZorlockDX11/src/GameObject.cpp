#include "GameObject.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"




GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::UpdateMatrix()
{
	//this->m_world = DirectX::XMMatrixScaling(this->scale[0], this->scale[1], this->scale[2]) * DirectX::XMMatrixTranslation(this->translate[0], this->translate[1], this->translate[2]) * DirectX::XMMatrixRotationRollPitchYaw(this->rotation[0], this->rotation[1], this->rotation[2]);
	assert("Override GameObject UpdateWorldMatrix Method");
}

void GameObject::Release()
{
}

const XMVECTOR & GameObject::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3 & GameObject::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR & GameObject::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3 & GameObject::GetRotationFloat3() const
{
	return this->rot;
}

void GameObject::SetPosition(const XMVECTOR & pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateMatrix();
}

void GameObject::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateMatrix();
}

void GameObject::AdjustPosition(const XMVECTOR & pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateMatrix();
}

void GameObject::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateMatrix();

}

void GameObject::SetRotation(const XMVECTOR & rot)
{
	XMStoreFloat3(&this->rot, rot);
	this->rotVector = rot;
	this->UpdateMatrix();
}

void GameObject::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateMatrix();
}

void GameObject::SetRotation(const XMFLOAT3 rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateMatrix();
}

void GameObject::AdjustRotation(const XMVECTOR & rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateMatrix();
}

void GameObject::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateMatrix();
}

void GameObject::SetScale(const XMVECTOR & pos)
{
	XMStoreFloat3(&this->scale, pos);
	this->scaleVector = pos;
	this->UpdateMatrix();
}

void GameObject::SetScale(float x, float y, float z)
{
	this->scale = XMFLOAT3(x, y, z);
	this->scaleVector = XMLoadFloat3(&this->scale);
	this->UpdateMatrix();
}

void GameObject::AdjustScale(const XMVECTOR & pos)
{
	this->scaleVector += pos;
	XMStoreFloat3(&this->scale, this->scaleVector);
	this->UpdateMatrix();
}

void GameObject::AdjustScale(float x, float y, float z)
{
	this->scale.x += x;
	this->scale.y += y;
	this->scale.z += z;
	this->scaleVector = XMLoadFloat3(&this->scale);
	this->UpdateMatrix();
}








