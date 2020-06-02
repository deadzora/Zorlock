#include "ZLpch.h"
#include "Bone.h"

namespace Zorlock
{
	
	Bone::Bone(std::string name, Ref<Transform> parent) : GameObject(name,parent) , m_bone_id(0), m_numweights(0)
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

	void Bone::SetBoneWeight(uint32_t submesh, float weight, uint32_t vertexid)
	{
		weights.push_back(BoneWeight(weight,vertexid,submesh));
	}

	void Bone::SetBoneWeight(BoneWeight bw)
	{
		weights.push_back(bw);
	}

	void Bone::SetOffset(Matrix4 mat)
	{
		offsetmat = mat;
	}

	Matrix4& Bone::GetOffset()
	{
		return offsetmat;
	}

	void Bone::SetBaseMat(Matrix4 mat)
	{
		basemat = mat;
	}

	Matrix4& Bone::GetBaseMat()
	{
		return basemat;
	}

	BoneWeight& Bone::GetBoneWeight(uint32_t i)
	{
		if (i > weights.size() - 1)
			return BoneWeight();

		return weights[i];
	}

	BoneWeight& Bone::GetBoneWeight(uint32_t sm, uint32_t vid)
	{
		for (size_t i = 0; i < weights.size(); i++)
		{
			if (weights[i].submesh == sm && weights[i].vertexid == vid)
				return weights[i];
		}
		return BoneWeight();
	}

	BoneWeight& Bone::operator[](int i)
	{
		return weights[i];
	}
	
	Bone::~Bone()
	{

	}
}