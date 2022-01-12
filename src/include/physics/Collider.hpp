#pragma once
#include "../geometry/main.hpp"
namespace physics
{
	struct Collider;
	struct CircleCollider;
	struct DynamicCollider;

	struct Transform
	{
		geometry::Vector position;
		geometry::Vector scale;
		geometry::Quaternion rotation;
		inline bool operator==(const Transform& other) const noexcept
		{
			return position == other.position && scale == other.scale && rotation == other.rotation;
		}
		inline bool operator!=(const Transform& other) const noexcept
		{
			return !(position == other.position && scale == other.scale && rotation == other.rotation);
		}
	};

	struct CollisionPoints
	{
		geometry::Vector a;
		geometry::Vector b;
		geometry::Vector normal;
		double depth;
		bool hasCollision = false;
		inline bool operator==(const CollisionPoints& other) const noexcept
		{
			return a == other.a && b == other.b && normal == other.normal && hasCollision == other.hasCollision;
		}

		inline bool operator!=(const CollisionPoints& other) const noexcept
		{
			return !(a == other.a && b == other.b && normal == other.normal && hasCollision == other.hasCollision);
		}
	};

	struct Collider
	{
		virtual Collider* Clone() const = 0;
		virtual ~Collider();
		virtual bool operator==(const Collider& other) const noexcept = 0;
		virtual bool operator!=(const Collider& other) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const noexcept = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const DynamicCollider* collider,
			const Transform& colliderTransform) const noexcept = 0;
	};

	struct CircleCollider : public Collider
	{
		geometry::Vector center = geometry::Vector();
		double radius = 0;
		CircleCollider();
		CircleCollider(geometry::Vector center, double radius);
		CircleCollider(const CircleCollider& c);
		virtual bool operator==(const Collider& other) const noexcept override;
		virtual bool operator!=(const Collider& other) const noexcept override;
		Collider* Clone() const override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const DynamicCollider* collider,
			const Transform& colliderTransform) const noexcept override;
	};

	struct DynamicCollider : public Collider
	{
		geometry::Vector pos;
		std::vector<geometry::Vector> points;
		DynamicCollider();
		DynamicCollider(const DynamicCollider& d) noexcept;
		DynamicCollider(geometry::Vector pos, geometry::Vector a, geometry::Vector b, geometry::Vector c, std::initializer_list<geometry::Vector> extra={}) noexcept;
		bool operator==(const Collider& other) const noexcept override;
		bool operator!=(const Collider& other) const noexcept override;
		Collider* Clone() const override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const DynamicCollider* collider,
			const Transform& colliderTransform) const noexcept override;
	};
}