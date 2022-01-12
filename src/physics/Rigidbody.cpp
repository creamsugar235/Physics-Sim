#include "../include/physics/Collision.hpp"
#include "../include/physics/OstreamOverloads.hpp"

namespace physics
{
	Rigidbody::Rigidbody(const Transform& t, Collider& c, bool isTrigger, double mass,
		bool usesGravity, double staticFriction, double dynamicFriction,
		double restitution) noexcept : CollisionObject(t, c, isTrigger)
	{
		_isDynamic = true;
		_mass = mass;
		_usesGravity = usesGravity;
		_staticFriction = staticFriction;
		_dynamicFriction = dynamicFriction;
		_restitution = restitution;
	}

	Rigidbody::Rigidbody(const Rigidbody& r) noexcept
		: CollisionObject((CollisionObject)r)
	{
		_isDynamic = true;
		_mass = r.GetMass();
		_usesGravity = r.UsesGravity();
		_staticFriction = r.GetStaticFriction();
		_dynamicFriction = r.GetDynamicFriction();
		_restitution = r.GetRestitution();
	}

	bool Rigidbody::operator==(const CollisionObject& other) const noexcept
	{
		Rigidbody tmp(*this);
		try
		{
			tmp = dynamic_cast<const Rigidbody&>(other);
		}
		catch (std::bad_alloc& c)
		{
			return false;
		}
		return GetHash() == tmp.GetHash();
	}

	bool Rigidbody::operator!=(const CollisionObject& other) const noexcept
	{
		Rigidbody tmp(*this);
		try
		{
			tmp = dynamic_cast<const Rigidbody&>(other);
		}
		catch (std::bad_alloc& c)
		{
			return true;
		}
		return GetHash() != other.GetHash();
	}

	void Rigidbody::ApplyForce(geometry::Vector f) noexcept
	{
		_velocity += f;
	}

	CollisionObject* Rigidbody::Clone() const noexcept
	{
		return new Rigidbody(*this);
	}

	double Rigidbody::GetDynamicFriction() const noexcept
	{
		return _dynamicFriction;
	}

	geometry::Vector Rigidbody::GetForce() const noexcept
	{
		return _force;
	}

	geometry::Vector Rigidbody::GetGravity() const noexcept
	{
		return _gravity;
	}

	int Rigidbody::GetHash() const noexcept
	{
		std::string s = _transform.position.ToString() + _transform.scale.ToString();
		s = s + std::to_string(_isDynamic) + std::to_string(_isTrigger);
		s = s + _force.ToString() + _gravity.ToString() + std::to_string(_dynamicFriction) +
		std::to_string(_staticFriction) + std::to_string(_restitution);
		int h = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			h = h * 31 + static_cast<int>(s[i]);
		}
		return h;
	}

	double Rigidbody::GetInvMass() const noexcept
	{
		return _invMass;
	}

	double Rigidbody::GetMass() const noexcept
	{
		return _mass;
	}

	double Rigidbody::GetRestitution() const noexcept
	{
		return _restitution;
	}
	double Rigidbody::GetStaticFriction() const noexcept
	{
		return _staticFriction;
	}
	geometry::Vector Rigidbody::GetVelocity() const noexcept
	{
		return _velocity;
	}
	void Rigidbody::SetDynamicFriction(double f) noexcept
	{
		_dynamicFriction = f;
	}

	void Rigidbody::SetForce(const geometry::Vector& f) noexcept
	{
		_force = f;
	}

	void Rigidbody::SetGravity(const geometry::Vector& g) noexcept
	{
		_gravity = g;
	}

	void Rigidbody::SetMass(double m) noexcept
	{
		_mass = m;
		if (m)
			_invMass = 1/m;
		else
			_invMass = 0;
	}

	void Rigidbody::SetRestitution(double r) noexcept
	{
		_restitution = r;
	}

	void Rigidbody::SetStaticFriction(double f) noexcept
	{
		_staticFriction = f;
	}

	void Rigidbody::SetUsesGravity(bool b) noexcept
	{
		_usesGravity = b;
	}

	void Rigidbody::SetVelocity(const geometry::Vector& v) noexcept
	{
		_velocity = v;
	}

	bool Rigidbody::UsesGravity() const noexcept
	{
		return _usesGravity;
	}
}