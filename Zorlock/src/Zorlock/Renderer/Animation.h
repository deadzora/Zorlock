#pragma once

namespace Zorlock
{
	struct Vector3;
	struct Quaternion;
	

	struct Vector3Key
	{
		Vector3Key(float t, Vector3 v);
		~Vector3Key();
		Vector3Key operator=(Vector3Key& v);
		float time;
		Ref<Vector3> value;
	};

	struct QuaternionKey
	{
		QuaternionKey(float t, Quaternion q);
		~QuaternionKey();
		QuaternionKey operator=(QuaternionKey& q);

		float time;
		Ref<Quaternion> value;
	};

	struct AnimationChannel
	{
	public:
		AnimationChannel(std::string bonename);
		AnimationChannel(uint32_t boneid);
		void AddPositionKey(float time, Vector3 v);
		void AddRotationKey(float time, Quaternion q);
		void AddScalingKey(float time, Vector3 v);
		Vector3 InterpolatedPosition(float time);
		Vector3 InterpolatedScale(float time);
		Quaternion InterpolatedRotation(float time);
		float m_duration;
		std::string m_boneName;
		uint32_t m_boneID;
		std::vector<Vector3Key> m_position_keys;
		std::vector<QuaternionKey> m_rotation_keys;
		std::vector<Vector3Key> m_scaling_keys;

	};

	class Animation
	{
	public:
		Animation(std::string name = "Animation");
		~Animation();
		void SetAnimationID(uint32_t id);
		uint32_t GetAnimationID();
		void SetDuration(float duration);
		float GetDuration();
		void SetCurrentAnimTime(float t);
		float GetCurrentAnimTime();
		Ref<AnimationChannel> CreateChannel(std::string boneName = "");
		Ref<AnimationChannel> GetChannel(std::string bonename);
		Ref<AnimationChannel> GetChannel(uint32_t boneid);
		std::string name;
	protected:
		float m_currentTime;
		float m_duration;
		uint32_t m_animid;
		std::vector<Ref<AnimationChannel>> m_animchannels;
	};



}