#include "../include/physics/Collider.hpp"

namespace physics
{
	DynamicCollider::DynamicCollider(const DynamicCollider& d) noexcept
	{
		this->pos = d.pos;
		this->points = d.points;
	}

	DynamicCollider::DynamicCollider(geometry::Vector pos,
		geometry::Vector a,
		geometry::Vector b,
		geometry::Vector c,
		std::initializer_list<geometry::Vector> extra) noexcept
	{
		this->pos = pos;
		points = {extra};
		points.insert(points.begin(), c);
		points.insert(points.begin(), b);
		points.insert(points.begin(), a);
	}

	bool DynamicCollider::operator==(const Collider& other) const noexcept
	{
		DynamicCollider tmp;
		try
		{
			tmp = dynamic_cast<const DynamicCollider&>(other);
		}
		catch (const std::bad_alloc& e)
		{
			return false;
		}
		return pos == tmp.pos && points == tmp.points;
	}

	bool DynamicCollider::operator!=(const Collider& other) const noexcept
	{
		DynamicCollider tmp;
		try
		{
			tmp = dynamic_cast<const DynamicCollider&>(other);
		}
		catch (const std::bad_alloc& e)
		{
			return true;
		}
		return pos != tmp.pos || points != tmp.points;
	}

	Collider::~Collider()
	{
	}


	Collider* DynamicCollider::Clone() const
	{
		return new DynamicCollider(*this);
	}

	CircleCollider::CircleCollider(geometry::Vector center, double radius)
	{
		this->center = center;
		this->radius = radius;
	}

	CircleCollider::CircleCollider(const CircleCollider& c)
	{
		this->radius = c.radius;
		this->center = c.center;
	}

	Collider* CircleCollider::Clone() const
	{
		return new CircleCollider(*this);
	}

	bool CircleCollider::operator==(const Collider& other) const noexcept
	{
		CircleCollider tmp = CircleCollider(geometry::Vector(0, 0), 0);
		try
		{
			CircleCollider tmp = dynamic_cast<const CircleCollider&>(other);
		}
		catch(const std::bad_alloc	& c)
		{
			return false;
		}
		return tmp.radius == radius && tmp.center == center;
	}

	bool CircleCollider::operator!=(const Collider& other) const noexcept
	{
		CircleCollider tmp = CircleCollider(geometry::Vector(0, 0), 0);
		try
		{
			CircleCollider tmp = dynamic_cast<const CircleCollider&>(other);
		}
		catch(const std::bad_alloc& c)
		{
			return true;
		}
		return tmp.radius != radius || tmp.center != center;
	}
}