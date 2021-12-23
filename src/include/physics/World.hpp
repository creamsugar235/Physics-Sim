#pragma once
#include "Object.hpp"

namespace physics
{
	class World;
	class Object;
	class World
	{
		public:
			std::string name;
			std::vector<Object* > objects;
			void AddObject(const Object& o);
			void RemoveObject(const Object& o);
			void Update();
	};
}