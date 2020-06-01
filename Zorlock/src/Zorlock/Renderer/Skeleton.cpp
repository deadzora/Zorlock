#include "ZLpch.h"
#include "Skeleton.h"
#include "Bone.h"

namespace Zorlock
{

	Skeleton::Skeleton(std::string name, Ref<Transform> parent) : GameObject(name,parent)
	{
		m_bone_id[""] = -1;
	}

	void Skeleton::AddBone(std::string name, Ref<Transform> parent)
	{
		Ref<Bone> mbone = CreateRef<Bone>(name, parent);
		m_bones.push_back(mbone);
		m_bones[m_bones.size() - 1]->SetBoneID((uint32_t)(m_bones.size() - 1));
		m_bone_id[name] = (int)m_bones.size() - 1;
	}

	Ref<Bone> Skeleton::GetBone(uint32_t i)
	{
		if (i >= m_bones.size())
			return nullptr;

		return m_bones[i];
	}

	Ref<Bone> Skeleton::GetBone(std::string name)
	{
		if(m_bone_id[name]==-1)
			return nullptr;
		return m_bones[m_bone_id[name]];
	}

	Skeleton::~Skeleton()
	{
	}




}
