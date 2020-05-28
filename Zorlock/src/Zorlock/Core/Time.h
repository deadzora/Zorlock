#pragma once
#include "Timer.h"

namespace Zorlock
{

	class Time
	{
	public:
		Time();
		~Time();

		float getTime()  { return mTimeSinceStart; }

		UINT64 getTimeMs()  { return mTimeSinceStartMs; }

		float getFrameDelta()  { return mFrameDelta; }

		float getFixedFrameDelta()  { return (float)(mFixedStep * MICROSEC_TO_SEC); }

		float getLastFrameTime()  { return (float)(mLastFrameTime * MICROSEC_TO_SEC); }

		float getLastFixedUpdateTime()  { return (float)(mLastFixedUpdateTime * MICROSEC_TO_SEC); }


		UINT64 getFrameIdx()  { return mCurrentFrame.load(); }


		UINT64 getTimePrecise() const;

		static Time* GetInstance();


		UINT64 getStartTimeMs() const { return mAppStartTime; }


		void _update();

		UINT32 _getFixedUpdateStep(UINT64& step);


		void _advanceFixedUpdate(UINT64 step);

		static const double MICROSEC_TO_SEC;
	private:

		static constexpr UINT32 MAX_ACCUM_FIXED_UPDATES = 200;

		static constexpr UINT32 NEW_FIXED_UPDATES_PER_FRAME = 4;

		float mFrameDelta = 0.0f; /**< Frame delta in seconds */
		float mTimeSinceStart = 0.0f; /**< Time since start in seconds */
		UINT64 mTimeSinceStartMs = 0u;
		bool mFirstFrame = true;

		UINT64 mAppStartTime = 0u; /**< Time the application started, in microseconds */
		UINT64 mLastFrameTime = 0u; /**< Time since last runOneFrame call, In microseconds */
		std::atomic<unsigned long> mCurrentFrame{ 0UL };

		// Fixed update
		UINT64 mFixedStep = 16666; // 60 times a second in microseconds
		UINT64 mLastFixedUpdateTime = 0;
		bool mFirstFixedFrame = true;
		UINT32 mNumRemainingFixedUpdates = MAX_ACCUM_FIXED_UPDATES;

		std::time_t mAppStartUpDate;

		Timer * mTimer;

	};


}