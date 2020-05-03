#pragma once
#include "GameObject.h"

class Object2D :
	public GameObject
{
public:
	Object2D();
	~Object2D();
protected:
	virtual void UpdateMatrix();
};

