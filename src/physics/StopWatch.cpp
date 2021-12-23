#include "../include/physics/StopWatch.hpp"
namespace physics
{
	void StopWatch::Start()
	{
		start = Clock::now();
	}

	void StopWatch::Stop()
	{
		stop = Clock::now();
	}

	void StopWatch::Reset()
	{
		start = Clock::now();
	}

	double StopWatch::Duration() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	}
}