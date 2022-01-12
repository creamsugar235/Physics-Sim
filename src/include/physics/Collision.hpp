#pragma once
#include <memory>
#include <initializer_list>
#include <functional>
#include "Collider.hpp"

namespace physics
{
	struct Collision;
	struct CollisionObject;
	struct Rigidbody;
	struct Collider;
	struct CircleCollider;
	struct DynamicCollider;
	struct Object;
	class Solver;
	
	struct Collision
	{
		CollisionObject* a = NULL;
		CollisionObject* b = NULL;
		CollisionPoints points;
	};

	struct CollisionObject
	{
		protected:
			Transform _transform;
			Transform _lastTransform;
			Collider* _collider = NULL;
			bool _isTrigger = false;
			bool _isDynamic = false;
			std::function<void(Collision&, double)> _onCollision;
		public:
			CollisionObject(const Transform& t, Collider& c, bool isTrigger) noexcept;
			CollisionObject(const CollisionObject& c) noexcept;
			virtual ~CollisionObject() noexcept;
			virtual CollisionObject* Clone() const noexcept;
			virtual bool operator==(const CollisionObject& other) const noexcept;
			virtual bool operator!=(const CollisionObject& other) const noexcept;
			bool IsTrigger() const noexcept;
			bool IsDynamic() const noexcept;
			Collider& GetCollider() const noexcept;
			virtual int GetHash() const noexcept;
			geometry::Vector GetPosition() const noexcept;
			geometry::Quaternion GetRotation() const noexcept;
			const Transform& GetTransform() const noexcept;
			const Transform& GetLastTransform() const noexcept;
			void SetCollider(Collider& c) noexcept;
			void SetIsTrigger(bool b) noexcept;
			void SetLastTransform(const Transform& t) noexcept;
			void SetPosition(const geometry::Vector& p) noexcept;
			void SetRotation(const geometry::Quaternion& q) noexcept;
			void SetTransform(const Transform& t) noexcept;
	};

	struct Rigidbody : public CollisionObject
	{
		protected:
			geometry::Vector _gravity;
			geometry::Vector _force;
			geometry::Vector _velocity;
			double _mass = 1;
			double _invMass = 1;
			bool _usesGravity = true;
			double _staticFriction = 0.5;
			double _dynamicFriction = 0.5;
			double _restitution = 0.5;
		public:
			Rigidbody(const Transform& t, Collider& c, bool isTrigger, double mass,
				bool usesGravity=true, double staticFriction=0.5, double dynamicFriction=0.5,
				double restitution=0.5) noexcept;
			Rigidbody(const Rigidbody& r) noexcept;
			virtual bool operator==(const CollisionObject& other) const noexcept override;
			virtual bool operator!=(const CollisionObject& other) const noexcept override;
			CollisionObject* Clone() const noexcept override;
			void ApplyForce(geometry::Vector f) noexcept;
			double GetDynamicFriction() const noexcept;
			geometry::Vector GetForce() const noexcept;
			geometry::Vector GetGravity() const noexcept;
			virtual int GetHash() const noexcept override;
			double GetMass() const noexcept;
			double GetInvMass() const noexcept;
			double GetRestitution() const noexcept;
			double GetStaticFriction() const noexcept;
			geometry::Vector GetVelocity() const noexcept;
			void SetDynamicFriction(double f) noexcept;
			void SetForce(const geometry::Vector& f) noexcept;
			void SetGravity(const geometry::Vector& g) noexcept;
			void SetMass(double m) noexcept;
			void SetRestitution(double r) noexcept;
			void SetStaticFriction(double f) noexcept;
			void SetUsesGravity(bool b) noexcept;
			void SetVelocity(const geometry::Vector& v) noexcept;
			bool UsesGravity() const noexcept;
	};
}