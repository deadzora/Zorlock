#pragma once

#include "foundation/Px.h"
#include "cooking/PxCooking.h"



namespace Zorlock
{
	

	class Physics
	{
	public:
		Physics();
		~Physics() = default;
		virtual void Init();
		virtual void End();

	private:
		physx::PxFoundation* mFoundation;
		physx::PxPhysics* mPhysics;
		physx::PxCooking* mCooking;
		physx::PxMaterial* mMaterial;
		physx::PxTolerancesScale mScale;
	};
}