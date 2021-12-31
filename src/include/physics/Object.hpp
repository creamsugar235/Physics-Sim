 #pragma once
#include <memory>
#include "../geometry/main.hpp"
#include "../SFML/Graphics.hpp"
#include "Event.hpp"

namespace physics
{
	struct Transform;
	struct Object;
	struct Collider;
	struct Object
	{
		float mass;
		geometry::Vector velocity;
		geometry::Vector force;
		std::unique_ptr<Collider> collider = NULL;
		std::unique_ptr<Transform> transform = NULL;
	};

	struct Transform
	{
		geometry::Point position;
		geometry::Point scale;
		geometry::Quaternion rotation;
	};
}