#pragma once
#include "Object2D.h"

class OrthoCamera : public Object2D
{
public:
	OrthoCamera();
	~OrthoCamera();

	void SetProjectionValues(float width, float height, float nearZ, float farZ);

	const XMMATRIX & GetOrthoMatrix() const;
	const XMMATRIX & GetWorldMatrix() const;

private:
	void UpdateMatrix() override;

	XMMATRIX orthoMatrix;
	//XMMATRIX worldMatrix;
};

