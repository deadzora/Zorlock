#include "ZLpch.h"
#include "Animation.h"
#include "Zorlock/Core/Math.h"

namespace Zorlock
{

	Animation::Animation(std::string name) : name(name), m_duration(0), m_animid(0), m_currentTime(0), m_animspeed(0.5f)
	{
	}

	Animation::~Animation()
	{

	}

	void Animation::SetAnimationID(uint32_t id)
	{
		m_animid = id;
	}

	uint32_t Animation::GetAnimationID()
	{
		return m_animid;
	}

	void Animation::SetDuration(float duration)
	{
		m_duration = duration;
	}

	float Animation::GetDuration()
	{
		return m_duration;
	}

	void Animation::SetCurrentAnimTime(float t)
	{
		m_currentTime = t;
	}

	float Animation::GetCurrentAnimTime()
	{
		return m_currentTime;
	}

	void Animation::SetAnimationSpeed(float s)
	{
		m_animspeed = s;
	}

	float Animation::GetAnimationSpeed()
	{
		return m_animspeed;
	}

	Ref<AnimationChannel> Animation::CreateChannel(std::string boneName)
	{
		Ref<AnimationChannel> channel = CreateRef<AnimationChannel>(boneName);
		channel->m_duration = m_duration;
		m_animchannels.push_back(channel);
		return channel;
	}

	Ref<AnimationChannel> Animation::GetChannel(std::string bonename)
	{
		for (size_t i = 0; i < m_animchannels.size(); i++)
		{
			if (m_animchannels[i]->m_boneName.compare(bonename) == 0)
				return m_animchannels[i];
		}
		return nullptr;
	}

	Ref<AnimationChannel> Animation::GetChannel(uint32_t boneid)
	{
		for (size_t i = 0; i < m_animchannels.size(); i++)
		{
			if (m_animchannels[i]->m_boneID== boneid)
				return m_animchannels[i];
		}
		return nullptr;
	}



	AnimationChannel::AnimationChannel(std::string bonename) : m_boneName(bonename), m_boneID(0), m_duration(0)
	{
		//printf("bone: %s \n", bonename.c_str());
	}

	AnimationChannel::AnimationChannel(uint32_t boneid) : m_boneName(""), m_boneID(boneid), m_duration(0)
	{
		//printf("bone: %u \n", boneid);
	}

	void AnimationChannel::AddPositionKey(float time, Vector3 v)
	{
		//printf("key time: %f \n", time);
		m_position_keys.push_back(Vector3Key(time, v));
	}

	void AnimationChannel::AddRotationKey(float time, Quaternion q)
	{
		//printf("key time: %f \n", time);
		m_rotation_keys.push_back(QuaternionKey(time, q));
	}

	void AnimationChannel::AddScalingKey(float time, Vector3 v)
	{
		//printf("key time: %f \n", time);
		m_scaling_keys.push_back(Vector3Key(time, v));
	}

	Vector3 AnimationChannel::InterpolatedPosition(float time)
	{
		// we need at least two values to interpolate...
		if(m_position_keys.size()==1)
			return Vector3(*m_position_keys[0].value.get());

		uint32_t vindex = 0;
		for (size_t i = 0; i < m_position_keys.size()-1; i++)
		{
			if (time < m_position_keys[i+1].time)
			{
				vindex = i;
				break;
			}
		}
		uint32_t vnext = vindex + 1;
		float delta = m_position_keys[vnext].time - m_position_keys[vindex].time;
		float factor = (time - m_position_keys[vindex].time) / delta;
		Vector3 start = Vector3(m_position_keys[vindex].value->x, m_position_keys[vindex].value->y, m_position_keys[vindex].value->z);
		Vector3 end = Vector3(m_position_keys[vnext].value->x, m_position_keys[vnext].value->y, m_position_keys[vnext].value->z);

		return Vector3::lerp(factor, start, end);			
	}

	Vector3 AnimationChannel::InterpolatedScale(float time)
	{
		// we need at least two values to interpolate...
		if (m_scaling_keys.size() == 1)
			return Vector3(*m_scaling_keys[0].value.get());

		uint32_t vindex = 0;
		for (size_t i = 0; i < m_scaling_keys.size() - 1; i++)
		{
			if (time < m_scaling_keys[i+1].time)
			{
				vindex = i;
				break;
			}
		}
		uint32_t vnext = vindex + 1;
		float delta = m_scaling_keys[vnext].time - m_scaling_keys[vindex].time;
		float factor = (time - m_scaling_keys[vindex].time) / delta;
		Vector3 start = Vector3(m_scaling_keys[vindex].value->x, m_scaling_keys[vindex].value->y, m_scaling_keys[vindex].value->z);
		Vector3 end = Vector3(m_scaling_keys[vnext].value->x, m_scaling_keys[vnext].value->y, m_scaling_keys[vnext].value->z);

		return Vector3::lerp(factor, start, end);
	}

	Quaternion AnimationChannel::InterpolatedRotation(float time)
	{
		// we need at least two values to interpolate...
		if (m_rotation_keys.size() == 1)
			return Quaternion(*m_rotation_keys[0].value.get());

		uint32_t vindex = 0;
		for (size_t i = 0; i < m_rotation_keys.size() - 1; i++)
		{
			if (time < m_rotation_keys[i+1].time)
			{
				vindex = i;
				break;
			}
		}
		
		uint32_t vnext = vindex + 1;
		float delta = m_rotation_keys[vnext].time - m_rotation_keys[vindex].time;
		float factor = (time - m_rotation_keys[vindex].time) / delta;
		Quaternion start = Quaternion(m_rotation_keys[vindex].value->x, m_rotation_keys[vindex].value->y, m_rotation_keys[vindex].value->z, m_rotation_keys[vindex].value->w);
		Quaternion end = Quaternion(m_rotation_keys[vnext].value->x, m_rotation_keys[vnext].value->y, m_rotation_keys[vnext].value->z, m_rotation_keys[vnext].value->w);

		return Quaternion::lerpB(start, end, factor);
	}

	Vector3Key::Vector3Key(float t, Vector3 v) : time(t), value(CreateRef<Vector3>(v))
	{
	}

	Vector3Key::~Vector3Key()
	{
	}

	Vector3Key Vector3Key::operator=(Vector3Key& v)
	{
		time = v.time; value = v.value; return *this;
	}

	QuaternionKey::QuaternionKey(float t, Quaternion q) : time(t), value(CreateRef<Quaternion>(q))
	{
	}

	QuaternionKey::~QuaternionKey()
	{
	}

	QuaternionKey QuaternionKey::operator=(QuaternionKey& q)
	{
		time = q.time; value = q.value; return *this;
	}

}