#pragma once


#pragma once
#include "Zorlock/Physics/Physics.h"

#include "foundation/Px.h"
#include "cooking/PxCooking.h"



namespace Zorlock
{


	class PhysXPhysics : public Physics
	{
	public:
		PhysXPhysics();
		~PhysXPhysics() = default;
		virtual void Init() override;
		virtual void End() override;
		void CreatePhysics();
		void DestroyPhysics();

	private:
		physx::PxFoundation* mFoundation;
		physx::PxPhysics* mPhysics;
		physx::PxCooking* mCooking;
		physx::PxMaterial* mMaterial;
		physx::PxTolerancesScale mScale;
	};
}