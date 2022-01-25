#pragma once
#include "Collider.hpp"
#include <functional>
#include <memory>

namespace physics
{
	struct CollisionObject;
	struct Collision
	{
		CollisionObject* a = NULL;
		CollisionObject* b = NULL;
		CollisionPoints points;
	};

	//0x06
	struct CollisionObject : public serialization::Serializable
	{
		protected:
			Transform _transform;
			Transform _lastTransform;
			std::unique_ptr<Collider> _collider;
			bool _isTrigger = false;
			bool _isDynamic = false;
			std::function<void(Collision&, f64)> _onCollision;
		public:
			CollisionObject() noexcept;
			CollisionObject(const Transform& t, Collider& c, bool isTrigger) noexcept;
			CollisionObject(const CollisionObject& c) noexcept;
			virtual ~CollisionObject() noexcept;
			virtual CollisionObject* Clone() const noexcept;
			virtual CollisionObject& operator=(const CollisionObject& other) noexcept;
			virtual bool operator==(const CollisionObject& other) const noexcept;
			virtual bool operator!=(const CollisionObject& other) const noexcept;
			serialization::Serializable* Deserialize(std::vector<byte> v) const override;
			bool IsTrigger() const noexcept;
			bool IsDynamic() const noexcept;
			Collider& GetCollider() const noexcept;
			virtual int GetHash() const noexcept;
			geometry::Vector GetPosition() const noexcept;
			std::function<void(Collision&, f64)> GetOnCollisionFunction() const noexcept;
			geometry::Quaternion GetRotation() const noexcept;
			const Transform& GetTransform() const noexcept;
			const Transform& GetLastTransform() const noexcept;
			std::vector<unsigned char> Serialize() const override;
			void SetCollider(Collider& c) noexcept;
			void SetIsTrigger(bool b) noexcept;
			void SetLastTransform(const Transform& t) noexcept;
			void SetPosition(const geometry::Vector& p) noexcept;
			void SetOnCollisionFunction(const std::function<void(Collision&, f64)> func) noexcept;
			void SetRotation(const geometry::Quaternion& q) noexcept;
			void SetTransform(const Transform& t) noexcept;
			const unsigned long TotalByteSize() const noexcept override;
	};
}