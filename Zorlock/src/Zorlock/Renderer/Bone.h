#pragma once
#include "Zorlock/Game/GameObject.h"


namespace Zorlock {

	class Bone : public GameObject
	{
	public:
		Bone(std::string name = "Light", Ref<Transform> parent = nullptr);
		uint32_t GetBoneID();
		void SetBoneID(uint32_t id);
		~Bone();
	protected:
		uint32_t m_bone_id;
	};



}