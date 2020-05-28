#include "ZLpch.h"

#include "Physics.h"
#include "Platform/PhysX/PhysXPhysics.h"


namespace Zorlock
{
	PhysXPhysics physics;

	void Physics::Init()
	{
		physics.Init();
	}

	void Physics::End()
	{
		physics.End();
	}


}