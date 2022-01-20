#pragma once
#include "Collider.hpp"

namespace physics
{
	
	//0x02
	struct BoxCollider : public Collider
	{
		geometry::Vector pos;
		geometry::Vector dimensions;
		BoxCollider() noexcept;
		BoxCollider(const geometry::Vector& pos, const geometry::Vector& dimensions) noexcept;
		BoxCollider(const BoxCollider& b) noexcept;
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
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const BoxCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const MeshCollider* collider,
			const Transform& colliderTransform) const noexcept override;
		std::vector<unsigned char> Serialize() const override;
		const unsigned long TotalByteSize() const noexcept override;
		serialization::Serializable* Deserialize(std::vector<byte> v) const override;
	};
}