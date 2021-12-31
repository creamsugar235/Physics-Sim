#include "Collision.hpp"
using namespace physics;
namespace algo
{
	CollisionPoints FindCircleDynamicCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const DynamicCollider* b, const Transform& tb
	);

	CollisionPoints FindDynamicCircleCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	);

	CollisionPoints FindCirlceCircleCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	);

	CollisionPoints FindDynamicDynamicCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const DynamicCollider* b, const Transform& tb
	);

}