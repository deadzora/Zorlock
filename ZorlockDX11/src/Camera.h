#pragma once
#include "GameObject.h"
#include "Object3D.h"
#include <DirectXMath.h>
using namespace DirectX;

class Camera : public Object3D
{
public:
	Camera();
	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
	const XMMATRIX & GetViewMatrix() const;
	const XMMATRIX & GetProjectionMatrix() const;
	void SetPosition(const XMVECTOR & pos) override;
	void SetPosition(float x, float y, float z) override;
	void AdjustPosition(const XMVECTOR & pos) override;
	void AdjustPosition(float x, float y, float z) override;
	void SetRotation(const XMVECTOR & rot) override;
	void SetRotation(float x, float y, float z) override;
	void AdjustRotation(const XMVECTOR & rot) override;
	void AdjustRotation(float x, float y, float z) override;
	void SetLookAtPos(XMFLOAT3 lookAtPos);
	~Camera();
private:
	void UpdateViewMatrix();

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;



};

