#include "ZLpch.h"
#include "Skeleton.h"
#include "Bone.h"

namespace Zorlock
{

	Skeleton::Skeleton(std::string name, Ref<Transform> parent) : GameObject(name,parent)
	{
		m_bone_id[""] = -1;
	}

	Ref<Bone> Skeleton::AddBone(std::string name, Ref<Transform> parent)
	{
		Ref<Bone> mbone = CreateRef<Bone>(name, parent);
		m_bones.push_back(mbone);
		m_transforms.push_back(mbone->transform);
		m_bones[m_bones.size() - 1]->SetBoneID((uint32_t)(m_bones.size() - 1));
		m_bone_id[name] = (int)m_bones.size() - 1;
		return mbone;
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

	Matrix4* Skeleton::GetBoneMatrices()
	{
		static std::vector<Matrix4> mats;
		mats.clear();
		for (size_t i = 0; i < m_bones.size(); i++)
		{
			mats.push_back(Matrix4(transform->parent->GetDrawMatrix() * m_globalInverse * m_bones[i]->GetBaseMat() * m_bones[i]->GetOffset()));

		}
		return mats.data();
	}

	float* Skeleton::GetBoneMatricesArray()
	{
		static std::vector<float> matsf;
		matsf.clear();
		for (size_t i = 0; i < m_bones.size(); i++)
		{
			Matrix4 m = Matrix4(transform->parent->GetDrawMatrix() * m_globalInverse * m_bones[i]->GetBaseMat() * m_bones[i]->GetOffset());
			float* f = m.To4x4PtrArray();
			for (size_t i = 0; i < 16; i++)
			{
				matsf.push_back(*f);
				++f;
			}
			
		}
		return matsf.data();
	}



	int Skeleton::BoneID(std::string name)
	{
		return m_bone_id[name];
	}

	size_t Skeleton::GetBonesSize()
	{
		return m_bones.size();
	}

	void Skeleton::SetGlobalInverse(Matrix4 mat)
	{
		m_globalInverse = mat;
	}

	Matrix4& Skeleton::GetGlobalInverse()
	{
		
		return m_globalInverse;
	}



	Skeleton::~Skeleton()
	{
	}




}
