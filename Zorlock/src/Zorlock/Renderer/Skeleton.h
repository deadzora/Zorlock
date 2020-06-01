#pragma once
#include "Zorlock/Game/GameObject.h"
#include <map>

namespace Zorlock {

	class Bone;

	class Skeleton : public GameObject
	{
	public:
		Skeleton(std::string name = "Skeleton", Ref<Transform> parent = nullptr);
		void AddBone(std::string name = "Skeleton", Ref<Transform> parent = nullptr);
		Ref<Bone> GetBone(uint32_t i);
		Ref<Bone> GetBone(std::string name);
		~Skeleton();
	protected:
		std::vector<Ref<Bone>> m_bones;
		std::map< std::string, int > m_bone_id;
	
	};



}