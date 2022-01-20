#include "../include/physics/Collision.hpp"

namespace physics
{
	BoxCollider::BoxCollider() noexcept
	{
		classCode = 0x02;
		pos = geometry::Vector(0, 0);
		dimensions = geometry::Vector(1, 1);
	}

	BoxCollider::BoxCollider(const geometry::Vector& pos, const geometry::Vector& dimensions) noexcept
	{
		classCode = 0x02;
		this->pos = pos;
		this->dimensions = dimensions;
		if (this->dimensions.x < 0) {this->dimensions.x = fabs(this->dimensions.x);}
		if (this->dimensions.y < 0) {this->dimensions.y = fabs(this->dimensions.y);}
	}

	BoxCollider::BoxCollider(const BoxCollider& b) noexcept
	{
		classCode = 0x02;
		this->pos = b.pos;
		this->dimensions = b.dimensions;
		if (this->dimensions.x < 0) {this->dimensions.x = fabs(this->dimensions.x);}
		if (this->dimensions.y < 0) {this->dimensions.y = fabs(this->dimensions.y);}
	}

	bool BoxCollider::operator==(const Collider& other) const noexcept
	{
		BoxCollider b;
		try
		{
			b = dynamic_cast<const BoxCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return false;
		}
		return b.pos == pos && b.dimensions == dimensions;
	}

	bool BoxCollider::operator!=(const Collider& other) const noexcept
	{
		BoxCollider b;
		try
		{
			b = dynamic_cast<const BoxCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return true;
		}
		return b.pos != pos || b.dimensions != dimensions;
	}
}