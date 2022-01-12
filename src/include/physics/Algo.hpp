#include "Collision.hpp"
using namespace physics;
namespace algo
{
	CollisionPoints FindDynamicCircleCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	);

	CollisionPoints FindCircleCircleCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	);

	CollisionPoints FindDynamicDynamicCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const DynamicCollider* b, const Transform& tb
	);

	bool DynamicColliderVectorIsColliding(
		const DynamicCollider* a, const Transform& ta,
		const geometry::Vector& b
	);
}