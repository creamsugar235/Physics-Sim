#include "../include/geometry/main.hpp"

namespace geometry
{
	Vector::Vector()
	{
	}
	
	Vector::Vector(Point start, Point direction)
	{
		this->start = start;
		this->direction = direction;
	}
}