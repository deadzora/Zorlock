#include "ZLpch.h"
#include "Skeleton.h"
#include "Bone.h"
#include "Animation.h"
#include "Zorlock/Core/Math.h"
#include "RendererAPI.h"

namespace Zorlock
{

	Skeleton::Skeleton(std::string name, Ref<Transform> parent) : GameObject(name,parent), root(nullptr), m_currentanimation(nullptr)
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
		if (m_bone_id[name] == 0)
		{
			root = mbone;
		}
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

	Ref<Bone> Skeleton::GetRoot()
	{
		return root;
	}

	Matrix4* Skeleton::GetBoneMatrices(uint32_t submesh)
	{
		static std::vector<Matrix4> mats;
		mats.clear();
		for (size_t i = 0; i < m_bones.size(); i++)
		{
			if (m_currentanimation == nullptr)
			{
				mats.push_back(Matrix4(transform->parent->GetDrawMatrix() * m_globalInverse * m_globalInverse.inverse() * m_bones[i]->GetParentMat() * m_bones[i]->GetBaseMat() * m_bones[i]->GetOffset(submesh)));
			}
			else {
				//Matrix4 rot = Matrix4::rotation(Quaternion::EulerAngles(Vector3(0, 180, 0)));
				mats.push_back(Matrix4(transform->parent->GetDrawMatrix() * m_globalInverse * m_globalInverse.inverse() * m_bones[i]->GetParentAnimMat() * m_bones[i]->GetAnimationMat() * m_bones[i]->GetOffset(submesh)));
			}
		}
		return mats.data();
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

	void Skeleton::SetCurrentAnimation(Ref<Animation> a)
	{
		m_currentanimation = a;
	}

	void Skeleton::UpdateAnimation(Ref<Bone> Bone, Matrix4 parentmat)
	{
		float t = m_currentanimation->GetCurrentAnimTime();
		Bone->SetParentAnimMat(parentmat);
		Bone->SetAnimationTime(m_currentanimation->GetCurrentAnimTime());
		Ref<AnimationChannel> achannel = m_currentanimation->GetChannel(Bone->name);
		Bone->SetAnimationChannel(achannel);
		//Next get Interpolated TRS
		Matrix4 aTransform = Matrix4::IDENTITY(); //Bone->GetBaseMat();

		if (achannel != nullptr)
		{
			Vector3 pos = achannel->InterpolatedPosition(t);
			Quaternion rot = achannel->InterpolatedRotation(t);
			Vector3 scale = achannel->InterpolatedScale(t);
			aTransform = Matrix4::TRS(pos, rot, scale);
		}

		Matrix4 parentTransform = parentmat * aTransform;
		Bone->SetAnimationMat(aTransform);

		for (size_t i = 0; i < Bone->m_bones.size(); i++)
		{
			UpdateAnimation(Bone->m_bones[i], parentTransform);
		}


		
	}

	void Skeleton::Update(Timestep ts)
	{
		GameObject::Update(ts);
		
		if (root != nullptr)
		{
			if (m_currentanimation != nullptr)
			{
				
				float mtime = m_currentanimation->GetCurrentAnimTime();
				mtime += m_currentanimation->GetAnimationSpeed() * ts.GetSeconds();
				float dur = m_currentanimation->GetDuration();
				if (mtime >= dur)
					mtime = 0;
				m_currentanimation->SetCurrentAnimTime(mtime);
				//printf("Updating anim: current %f duration %f \n", mtime,dur);
				switch (RendererAPI::GetAPI())
				{
				case RendererAPI::API::DX11:
				{
					UpdateAnimation(root, Matrix4::rotation(Quaternion::EulerAngles(Vector3(0, 180, 0))) * m_globalInverse);
					break;
				}
				case RendererAPI::API::OpenGL:
				{
					UpdateAnimation(root, m_globalInverse);
					break;
				}
				}
				


			}
		}

	}



	Skeleton::~Skeleton()
	{
	}




}
