#include "include/physics/Scene.hpp"
#include <iostream>
#include <chrono>
using namespace physics;

class Time final
{
	public:
		typedef std::chrono::steady_clock clock;
		static inline std::chrono::time_point<clock> time = clock::now();
		static inline double deltaTime = -1;
		static void Tick();
};
void Time::Tick()
{
	std::chrono::time_point<clock> t = clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - time).count();
	time = clock::now();
}

int main(int argc, char** args)
{
	Scene s(geometry::Vector(0, -9.81), 0);
	Time __t__;
	while (s.display->GetWindow()->isOpen())
	{
		Time::Tick();
		s.Step(Time::deltaTime);
		s.display->Update();
	}
	return 0;
}