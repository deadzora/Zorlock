#include "ZLpch.h"
#include "Bone.h"

namespace Zorlock
{
	
	Bone::Bone(std::string name, Ref<Transform> parent) : GameObject(name,parent) , m_bone_id(0), m_numweights(0), offsetmat(Matrix4::IDENTITY()), basemat(Matrix4::IDENTITY()), animationmat(Matrix4::IDENTITY()), parentmat(Matrix4::IDENTITY()), m_currentChannel(nullptr), m_currentTime(0)
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

	void Bone::SetOffset(Matrix4 mat,uint32_t offset)
	{
	
		offsetmats[offset] = CreateRef<Matrix4>(mat);
		//printf("Set offset %s for submesh: %u \n", name.c_str(),(uint32_t)offsetmats.size()-1);

	}

	void Bone::SetAnimationMat(Matrix4 mat)
	{
		animationmat = mat;
	}

	void Bone::SetParentMat(Matrix4 mat)
	{
		parentmat = mat;
	}

	void Bone::SetParentAnimMat(Matrix4 mat)
	{
		parentanimmat = mat;
	}

	void Bone::AddChildBone(Ref<Bone> bone)
	{
		m_bones.push_back(bone);
	}

	Matrix4& Bone::GetParentMat()
	{
		return parentmat;
	}

	Matrix4& Bone::GetParentAnimMat()
	{
		return parentanimmat;
	}

	Matrix4& Bone::GetAnimationMat()
	{
		return animationmat;
	}

	Matrix4 Bone::GetOffset(uint32_t submesh)
	{
		if (offsetmats[submesh] != nullptr)
		{
			return Matrix4(*offsetmats[submesh].get());
		}
		
		return Matrix4::ZERO();

	}



	Matrix4 Bone::GetFinalTransform()
	{
		return parentmat * basemat * offsetmat;
	}

	Matrix4 Bone::GetFinalAnimTransform()
	{
		return parentanimmat * animationmat * offsetmat;
	}

	void Bone::SetParent(Ref<Bone> bone)
	{
		parent = bone;
	}

	Ref<Bone> Bone::GetParent()
	{
		return parent;
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

	void Bone::SetAnimationChannel(Ref<AnimationChannel> channel)
	{
		m_currentChannel = channel;
	}

	void Bone::SetAnimationTime(float t)
	{
		m_currentTime = t;
	}

	void Bone::Update(Timestep ts)
	{
		GameObject::Update(ts);
		if (m_currentChannel != nullptr)
		{

		}
	}

	BoneWeight& Bone::operator[](int i)
	{
		return weights[i];
	}
	
	Bone::~Bone()
	{

	}
}