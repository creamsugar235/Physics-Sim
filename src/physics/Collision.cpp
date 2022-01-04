#include "../include/physics/Collision.hpp"
#include "../include/physics/Algo.hpp"

namespace physics
{

	DynamicCollider::DynamicCollider(const DynamicCollider& d)
	{
		this->pos = d.pos;
		this->points = d.points;
	}

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

	CircleCollider::CircleCollider(const CircleCollider& c)
	{
		this->radius = c.radius;
		this->center = c.center;
	}

	CollisionPoints CircleCollider::TestCollision(const Transform& transform,
		const Collider* collider,
		const Transform& colliderTransform) const
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints CircleCollider::TestCollision(const Transform& transform,
		const CircleCollider* collider,
		const Transform& colliderTransform) const
	{
		return algo::FindCircleCircleCollisionPoints(this, transform, collider, colliderTransform);
	}

	CollisionPoints CircleCollider::TestCollision(const Transform& transform,
		const DynamicCollider* collider,
		const Transform& colliderTransform) const
	{
		return algo::FindDynamicCircleCollisionPoints(collider, colliderTransform, this, transform);
	}

	CollisionPoints DynamicCollider::TestCollision(const Transform& transform,
		const Collider* collider,
		const Transform& colliderTransform) const
	{
		return collider->TestCollision(colliderTransform, this, transform);
	}

	CollisionPoints DynamicCollider::TestCollision(const Transform& transform,
		const CircleCollider* collider,
		const Transform& colliderTransform) const
	{
		return algo::FindDynamicCircleCollisionPoints(this, transform, collider, colliderTransform);
	}

	CollisionPoints DynamicCollider::TestCollision(const Transform& transform,
		const DynamicCollider* collider,
		const Transform& colliderTransform) const
	{
		return algo::FindDynamicDynamicCollisionPoints(this, transform, collider, colliderTransform);
	}

	CollisionObject::CollisionObject(const Transform& t, std::shared_ptr<Collider> c, bool isTrigger)
	{
		_transform = t;
		_collider = c;
		_isTrigger = isTrigger;
	}

	CollisionObject::~CollisionObject()
	{
	}

	bool CollisionObject::IsTrigger()
	{
		return _isTrigger;
	}

	bool CollisionObject::IsDynamic()
	{
		return _isDynamic;
	}

	std::shared_ptr<Collider> CollisionObject::GetCollider() const
	{
		return _collider;
	}

	geometry::Point CollisionObject::GetPosition() const
	{
		return _transform.position;
	}

	geometry::Quaternion CollisionObject::GetRotation() const
	{
		return _transform.rotation;
	}

	const Transform& CollisionObject::GetTransform() const
	{
		return _transform;
	}

	const Transform& CollisionObject::GetLastTransform() const
	{
		return _lastTransform;
	}

	void CollisionObject::SetCollider(Collider* c)
	{
		_collider.reset(c);
	}

	void CollisionObject::SetLastTransform(const Transform& t)
	{
		_lastTransform = t;
	}

	void CollisionObject::SetIsTrigger(bool b)
	{
		_isTrigger = b;
	}

	void CollisionObject::SetPosition(const geometry::Point& p)
	{
		_transform.position = p;
	}

	void CollisionObject::SetRotation(const geometry::Quaternion& q)
	{
		_transform.rotation = q;
	}

	void CollisionObject::SetTransform(const Transform& t)
	{
		_lastTransform = _transform;
		_transform = t;
	}
}