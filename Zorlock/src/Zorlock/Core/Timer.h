#pragma once

namespace Zorlock
{

	class Timer
	{
	public:
		Timer();
		~Timer();
		void reset();
		UINT64 getMilliseconds() const;
		UINT64 getMicroseconds() const;
		UINT64 getStartMs() const;
	private:
		std::chrono::high_resolution_clock mHRClock;
		std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;

	};


}