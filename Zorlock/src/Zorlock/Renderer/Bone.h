#pragma once
#include "Zorlock/Game/GameObject.h"
#include <map>

namespace Zorlock {

	struct AnimationChannel;

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
		void SetOffset(Matrix4 mat, uint32_t offset);
		void SetAnimationMat(Matrix4 mat);
		void SetParentMat(Matrix4 mat);
		void SetParentAnimMat(Matrix4 mat);
		void AddChildBone(Ref<Bone> bone);
		Matrix4& GetParentMat();
		Matrix4& GetParentAnimMat();
		Matrix4& GetAnimationMat();
		Matrix4 GetOffset(uint32_t submesh = 0);
		Matrix4 GetFinalTransform();
		Matrix4 GetFinalAnimTransform();
		void SetParent(Ref<Bone> bone);
		Ref<Bone> GetParent();
		void SetBaseMat(Matrix4 mat);
		Matrix4& GetBaseMat();
		BoneWeight& GetBoneWeight(uint32_t i);
		BoneWeight& GetBoneWeight(uint32_t sm, uint32_t vid);
		void SetAnimationChannel(Ref<AnimationChannel> channel);
		void SetAnimationTime(float t);
		virtual void Update(Timestep ts) override;
		BoneWeight& operator[](int i);
		std::vector<Ref<Bone>> m_bones;
		~Bone();
	protected:
		float m_currentTime;	
		Ref<AnimationChannel> m_currentChannel;
		Ref<Bone> parent;
		Matrix4 parentmat;
		std::map<uint32_t,Ref<Matrix4>> offsetmats;
		Matrix4 offsetmat;
		Matrix4 animationmat;
		Matrix4 parentanimmat;
		Matrix4 basemat;
		uint32_t m_numweights;
		uint32_t m_bone_id;
		std::vector<BoneWeight> weights;
	};



}