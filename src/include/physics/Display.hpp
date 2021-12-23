#pragma once
#include <chrono>
#include "Global.hpp"
#include "World.hpp"
#include "Object.hpp"
#include "../SFML/Graphics.hpp"
#include "../SFML/Window.hpp"

namespace physics
{
	void CheckCollision();
	void Display();
	bool IsInView(Object* o);
	void Load();
	void Run();
	void Start();
	
	class Time;
	class Time final
	{
		public:
			typedef std::chrono::steady_clock clock;
			static inline std::chrono::time_point<clock> time = clock::now();
			static inline double deltaTime = -1;
			static void Tick();
	};
}