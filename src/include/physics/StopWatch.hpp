#pragma once
#include <ctime>
#include <chrono>
#include "Global.hpp"
namespace physics
{
	class StopWatch;

	class StopWatch
	{
		public:
			typedef std::chrono::high_resolution_clock Clock;
			std::chrono::time_point<std::chrono::high_resolution_clock> start;
			std::chrono::time_point<std::chrono::high_resolution_clock> stop;
			void Reset();
			void Start();
			void Stop();
			double Duration() const;
	};
}