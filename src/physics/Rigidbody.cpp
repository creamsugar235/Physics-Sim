#include "../include/physics/Collision.hpp"

namespace physics
{
	Rigidbody::Rigidbody(const Transform& t, Collider& c, bool isTrigger, double mass,
		bool usesGravity, double staticFriction, double dynamicFriction,
		double restitution) : CollisionObject(t, c, isTrigger)
	{
		_isDynamic = true;
		_mass = mass;
		_usesGravity = usesGravity;
		_staticFriction = staticFriction;
		_dynamicFriction = dynamicFriction;
		_restitution = restitution;
	}

	Rigidbody::Rigidbody(const Rigidbody& r)
		: CollisionObject(r.GetTransform(), r.GetCollider(), r.IsTrigger())
	{
		_isDynamic = true;
		_mass = r.GetMass();
		_usesGravity = r.UsesGravity();
		_staticFriction = r.GetStaticFriction();
		_dynamicFriction = r.GetDynamicFriction();
		_restitution = r.GetRestitution();
	}

	void Rigidbody::ApplyForce(geometry::Vector f)
	{
		_velocity += f;
	}

	CollisionObject* Rigidbody::Clone() const
	{
		return new Rigidbody(*this);
	}

	double Rigidbody::GetDynamicFriction() const
	{
		return _dynamicFriction;
	}

	geometry::Vector Rigidbody::GetForce() const
	{
		return _force;
	}

	geometry::Vector Rigidbody::GetGravity() const
	{
		return _gravity;
	}

	double Rigidbody::GetInvMass() const
	{
		return _invMass;
	}

	double Rigidbody::GetMass() const
	{
		return _mass;
	}

	double Rigidbody::GetRestitution() const
	{
		return _restitution;
	}
	double Rigidbody::GetStaticFriction() const
	{
		return _staticFriction;
	}
	geometry::Vector Rigidbody::GetVelocity() const
	{
		return _velocity;
	}
	void Rigidbody::SetDynamicFriction(double f)
	{
		_dynamicFriction = f;
	}

	void Rigidbody::SetForce(const geometry::Vector& f)
	{
		_force = f;
	}

	void Rigidbody::SetGravity(const geometry::Vector& g)
	{
		_gravity = g;
	}

	void Rigidbody::SetMass(double m)
	{
		_mass = m;
		if (m)
			_invMass = 1/m;
		else
			_invMass = 0;
	}

	void Rigidbody::SetRestitution(double r)
	{
		_restitution = r;
	}

	void Rigidbody::SetStaticFriction(double f)
	{
		_staticFriction = f;
	}

	void Rigidbody::SetUsesGravity(bool b)
	{
		_usesGravity = b;
	}

	void Rigidbody::SetVelocity(const geometry::Vector& v)
	{
		_velocity = v;
	}

	bool Rigidbody::UsesGravity() const
	{
		return _usesGravity;
	}
}