#include "../include/physics/Collision.hpp"

namespace physics
{
	DynamicCollider::DynamicCollider(geometry::Point pos,
		geometry::Point a,
		geometry::Point b,
		geometry::Point c,
		std::initializer_list<geometry::Point> extra)
	{
		this->pos = pos;
		points = {extra};
		points.insert(points.begin(), c);
		points.insert(points.begin(), b);
		points.insert(points.begin(), a);
	}
}