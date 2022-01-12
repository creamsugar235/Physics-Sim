#include "include/physics/Scene.hpp"
#include "include/SFML/Graphics.hpp"
#include "physics/main.hpp"
#include "test.cpp"
#include <iostream>
#include <chrono>
using namespace physics;
using namespace geometry;

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
	if (!test::TestCollisionChecking())
	{
		std::cerr<<"failed\n\a";
		exit(1);
	} else if (!test::TestColliders())
	{
		std::cerr<<"failed\n\a";
		exit(1);
	} else if (!test::TestCollisionObject())
	{
		std::cerr<<"failed\n\a";
		exit(1);
	}
	std::cout<<"Success!\n";
	return 0;
}