#pragma once
#include "Zorlock/Game/GameObject.h"


namespace Zorlock {

	struct BoneWeight
	{
		BoneWeight() : weight(0.0f), vertexid(0), submesh(0)
		{}
		BoneWeight(float w, uint32_t vi, uint32_t sm) : weight(w), vertexid(vi), submesh(sm)
		{}
		~BoneWeight(){}
		float weight;
		uint32_t vertexid;
		uint32_t submesh;

		BoneWeight operator=(BoneWeight& b)
		{
			weight = b.weight; vertexid = b.vertexid; submesh = b.submesh; return *this;
		}
	};
	
	class Bone : public GameObject
	{
	public:
		Bone(std::string name = "Bone", Ref<Transform> parent = nullptr);
		uint32_t GetBoneID();
		void SetBoneID(uint32_t id);
		void SetBoneWeight(uint32_t submesh, float weight, uint32_t vertexid);
		void SetBoneWeight(BoneWeight bw);
		BoneWeight& GetBoneWeight(uint32_t i);
		BoneWeight& GetBoneWeight(uint32_t sm, uint32_t vid);
		BoneWeight& operator[](int i);
		~Bone();
	protected:
		uint32_t m_numweights;
		uint32_t m_bone_id;
		std::vector<BoneWeight> weights;
	};



}