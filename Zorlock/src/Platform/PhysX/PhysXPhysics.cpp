#include "ZLpch.h"

#include "PhysXPhysics.h"

#include "PxPhysicsAPI.h"


using namespace physx;

namespace Zorlock
{
	class PhysXAllocator : public PxAllocatorCallback
	{
	public:
		void* allocate(size_t size, const char*, const char*, int) override
		{
			void* ptr = _aligned_malloc((UINT32)size, 15);
			PX_ASSERT((reinterpret_cast<size_t>(ptr) & 15) == 0);
			return ptr;
		}

		void deallocate(void* ptr) override
		{
			_aligned_free(ptr);
		}
	};

	class PhysXErrorCallback : public PxErrorCallback
	{
	public:
		void reportError(PxErrorCode::Enum code, const char* message, const char* file, int line) override
		{
			const char* errorCode = nullptr;

			UINT32 severity = 0;

			if ((code & PxErrorCode::eDEBUG_INFO) != 0)
			{
				errorCode = "Info";
				severity = 0;
			}

			if ((code & PxErrorCode::eINVALID_PARAMETER) != 0)
			{
				errorCode = "Invalid parameter";
				severity = 1;
			}

			if ((code & PxErrorCode::eINVALID_OPERATION) != 0)
			{
				errorCode = "Invalid operation";
				severity = 1;
			}

			if ((code & PxErrorCode::eDEBUG_WARNING) != 0)
			{
				errorCode = "Generic";
				severity = 1;
			}

			if ((code & PxErrorCode::ePERF_WARNING) != 0)
			{
				errorCode = "Performance";
				severity = 1;
			}

			if ((code & PxErrorCode::eOUT_OF_MEMORY) != 0)
			{
				errorCode = "Out of memory";
				severity = 2;
			}

			if ((code & PxErrorCode::eABORT) != 0)
			{
				errorCode = "Abort";
				severity = 2;
			}

			if ((code & PxErrorCode::eINTERNAL_ERROR) != 0)
			{
				errorCode = "Internal";
				severity = 2;
			}

			std::stringstream ss;

			switch (severity)
			{
			case 0:
				ss << "PhysX info (" << errorCode << "): " << message << " at " << file << ":" << line;
				ZL_CORE_INFO(ss.str());
				break;
			case 1:
				ss << "PhysX warning (" << errorCode << "): " << message << " at " << file << ":" << line;
				ZL_CORE_WARN(ss.str());
				break;
			case 2:
				ss << "PhysX error (" << errorCode << "): " << message << " at " << file << ":" << line;
				ZL_CORE_ERROR(ss.str());
				// Halt execution on debug builds when error occurs
				break;
			}
		}
	};

	static PhysXAllocator gPhysXAllocator;
	static PhysXErrorCallback gPhysXErrorHandler;

	void PhysXPhysics::Init()
	{
		CreatePhysics();
	}

	void PhysXPhysics::End()
	{
		DestroyPhysics();
	}

	void PhysXPhysics::CreatePhysics()
	{
		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gPhysXAllocator, gPhysXErrorHandler);
		if (mFoundation)
		{
			ZL_CORE_INFO("Foundation Initialized");
		}

		mScale.length = PxTolerancesScale().length;
		mScale.speed = PxTolerancesScale().speed;

		mPhysics = PxCreateBasePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale());
		if (mPhysics)
		{
			ZL_CORE_INFO("Physics Initialized");
		}

		PxCookingParams cookingParams(mScale);
		mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, cookingParams);
		if (mCooking)
		{
			ZL_CORE_INFO("Cooking Initialized");
		}
	}

	void PhysXPhysics::DestroyPhysics()
	{
		mPhysics->release();

		mFoundation->release();
	}

}