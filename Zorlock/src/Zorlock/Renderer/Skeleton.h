#pragma once
#include "Zorlock/Game/GameObject.h"
#include <map>

namespace Zorlock {

	class Bone;

	class Skeleton : public GameObject
	{
	public:
		Skeleton(std::string name = "Skeleton", Ref<Transform> parent = nullptr);
		Ref<Bone> AddBone(std::string name = "Skeleton", Ref<Transform> parent = nullptr);
		Ref<Bone> GetBone(uint32_t i);
		Ref<Bone> GetBone(std::string name);
		Matrix4* GetBoneMatrices();
		float* GetBoneMatricesArray();
		int BoneID(std::string name);
		size_t GetBonesSize();
		void SetGlobalInverse(Matrix4 mat);
		Matrix4& GetGlobalInverse();
		~Skeleton();
	protected:
		Matrix4 m_globalInverse;
		std::vector<Ref<Bone>> m_bones;
		std::vector<Ref<Transform>> m_transforms;
		std::map< std::string, int > m_bone_id;
	
	};



}