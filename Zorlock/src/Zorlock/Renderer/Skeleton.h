#pragma once
#include "Zorlock/Game/GameObject.h"
#include <map>

namespace Zorlock {

	class Bone;
	class Animation;

	class Skeleton : public GameObject
	{
	public:
		Skeleton(std::string name = "Skeleton", Ref<Transform> parent = nullptr);
		Ref<Bone> AddBone(std::string name = "Skeleton", Ref<Transform> parent = nullptr);
		Ref<Bone> GetBone(uint32_t i);
		Ref<Bone> GetBone(std::string name);
		Ref<Bone> GetRoot();
		Matrix4* GetBoneMatrices(uint32_t submesh = 0);
		float* GetBoneMatricesArray();
		int BoneID(std::string name);
		size_t GetBonesSize();
		void SetGlobalInverse(Matrix4 mat);
		Matrix4& GetGlobalInverse();
		void SetCurrentAnimation(Ref<Animation> a);
		void UpdateAnimation(Ref<Bone> Bone, Matrix4 parentmat);
		virtual void Update(Timestep ts) override;
		~Skeleton();
	protected:
		Ref<Animation> m_currentanimation;
		Ref<Bone> root;
		Matrix4 m_globalInverse;
		std::vector<Ref<Bone>> m_bones;
		std::vector<Ref<Transform>> m_transforms;
		std::map< std::string, int > m_bone_id;
	
	};



}