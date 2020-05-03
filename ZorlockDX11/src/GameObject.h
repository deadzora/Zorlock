#pragma once
#include "zObject.h"
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class GameObject :
	public zObject
{
public:
	GameObject();
	~GameObject();
	void Release();
	const XMVECTOR & GetPositionVector() const;
	const XMFLOAT3 & GetPositionFloat3() const;
	const XMVECTOR & GetRotationVector() const;
	const XMFLOAT3 & GetRotationFloat3() const;
	virtual void SetPosition(const XMVECTOR & pos);
	virtual void SetPosition(float x, float y, float z);
	virtual void AdjustPosition(const XMVECTOR & pos);
	virtual void AdjustPosition(float x, float y, float z);
	virtual void SetRotation(const XMVECTOR & rot);
	virtual void SetRotation(float x, float y, float z);
	virtual void SetRotation(const XMFLOAT3 rot);
	virtual void AdjustRotation(const XMVECTOR & rot);
	virtual void AdjustRotation(float x, float y, float z);
	virtual void SetScale(const XMVECTOR & pos);
	virtual void SetScale(float x, float y, float z);
	virtual void AdjustScale(const XMVECTOR & pos);
	virtual void AdjustScale(float x, float y, float z);
	
protected:
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMVECTOR scaleVector;
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 scale;
	virtual void UpdateMatrix();
	XMMATRIX m_world = XMMatrixIdentity();
	
};

