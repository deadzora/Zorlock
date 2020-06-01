#include "ZLpch.h"
#include "Bone.h"

namespace Zorlock
{
	
	Bone::Bone(std::string name, Ref<Transform> parent) : GameObject(name,parent)
	{

	}

	uint32_t Bone::GetBoneID()
	{
		return m_bone_id;
	}

	void Bone::SetBoneID(uint32_t id)
	{
		m_bone_id = id;
	}
	
	Bone::~Bone()
	{

	}
}