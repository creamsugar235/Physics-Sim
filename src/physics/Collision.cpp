#include "../include/physics/Collision.hpp"
#include "../include/physics/Algo.hpp"
#include "../include/physics/OstreamOverloads.hpp"
#include <iostream>

namespace physics
{

	CollisionPoints CircleCollider::TestCollision(const Transform& transform,
		const Collider* collider,
		const Transform& colliderTransform) const noexcept
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints CircleCollider::TestCollision(const Transform& transform,
		const CircleCollider* collider,
		const Transform& colliderTransform) const noexcept
	{
		return algo::FindCircleCircleCollisionPoints(this, transform, collider, colliderTransform);
	}

	CollisionPoints CircleCollider::TestCollision(const Transform& transform,
		const DynamicCollider* collider,
		const Transform& colliderTransform) const noexcept
	{
		return algo::FindDynamicCircleCollisionPoints(collider, colliderTransform, this, transform);
	}

	CollisionPoints DynamicCollider::TestCollision(const Transform& transform,
		const Collider* collider,
		const Transform& colliderTransform) const noexcept
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints DynamicCollider::TestCollision(const Transform& transform,
		const CircleCollider* collider,
		const Transform& colliderTransform) const noexcept
	{
		return algo::FindDynamicCircleCollisionPoints(this, transform, collider, colliderTransform);
	}

	CollisionPoints DynamicCollider::TestCollision(const Transform& transform,
		const DynamicCollider* collider,
		const Transform& colliderTransform) const noexcept
	{
		return algo::FindDynamicDynamicCollisionPoints(this, transform, collider, colliderTransform);
	}

	CollisionObject::CollisionObject(const Transform& t, Collider& c, bool isTrigger) noexcept
	{
		_transform = t;
		_collider = c.Clone();
		_isTrigger = isTrigger;
	}

	CollisionObject::CollisionObject(const CollisionObject& c) noexcept
	{
		_transform = c.GetTransform();
		_collider = c.GetCollider().Clone();
		_isTrigger = c.IsTrigger();
	}

	bool CollisionObject::operator==(const CollisionObject& other) const noexcept
	{
		return _transform == other.GetTransform() && *_collider == other.GetCollider();
	}

	bool CollisionObject::operator!=(const CollisionObject& other) const noexcept
	{
		return _transform != other.GetTransform() || *_collider != other.GetCollider();
	}

	CollisionObject* CollisionObject::Clone() const noexcept
	{
		return new CollisionObject(*this);
	}

	CollisionObject::~CollisionObject()
	{
		delete _collider;
	}

	bool CollisionObject::IsTrigger() const noexcept
	{
		return _isTrigger;
	}

	bool CollisionObject::IsDynamic() const noexcept
	{
		return _isDynamic;
	}

	Collider& CollisionObject::GetCollider() const noexcept
	{
		return *_collider;
	}

	int CollisionObject::GetHash() const noexcept
	{
		std::string s = _transform.position.ToString() + _transform.scale.ToString();
		s = s + std::to_string(_isDynamic) + std::to_string(_isTrigger);
		int h = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			h = h * 31 + static_cast<int>(s[i]);
		}
		return h;
	}

	geometry::Vector CollisionObject::GetPosition() const noexcept
	{
		return _transform.position;
	}

	geometry::Quaternion CollisionObject::GetRotation() const noexcept
	{
		return _transform.rotation;
	}

	const Transform& CollisionObject::GetTransform() const noexcept
	{
		return _transform;
	}

	const Transform& CollisionObject::GetLastTransform() const noexcept
	{
		return _lastTransform;
	}

	void CollisionObject::SetCollider(Collider& c) noexcept
	{
		delete _collider;
		_collider = c.Clone();
	}

	void CollisionObject::SetLastTransform(const Transform& t) noexcept
	{
		_lastTransform = t;
	}

	void CollisionObject::SetIsTrigger(bool b) noexcept
	{
		_isTrigger = b;
	}

	void CollisionObject::SetPosition(const geometry::Vector& p) noexcept
	{
		_transform.position = p;
	}

	void CollisionObject::SetRotation(const geometry::Quaternion& q) noexcept
	{
		_transform.rotation = q;
	}

	void CollisionObject::SetTransform(const Transform& t) noexcept
	{
		_lastTransform = _transform;
		_transform = t;
	}
}