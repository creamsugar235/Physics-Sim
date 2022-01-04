#pragma once
#include <memory>
#include <initializer_list>
#include <functional>
#include "Object.hpp"

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

	struct CollisionPoints
	{
		geometry::Vector a;
		geometry::Vector b;
		geometry::Vector normal;
		double depth;
		bool hasCollision = false;
	};

	struct Collider
	{
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const = 0;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const DynamicCollider* collider,
			const Transform& colliderTransform) const = 0;
	};

	struct CircleCollider : public Collider
	{
		geometry::Point center;
		double radius;
		CircleCollider(const CircleCollider& c);
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const DynamicCollider* collider,
			const Transform& colliderTransform) const override;
	};

	struct DynamicCollider : public Collider
	{
		geometry::Point pos;
		std::vector<geometry::Point> points;
		DynamicCollider(const DynamicCollider& d);
		DynamicCollider(geometry::Point pos, geometry::Point a, geometry::Point b, geometry::Point c, std::initializer_list<geometry::Point> extra);
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const Collider* collider,
			const Transform& colliderTransform) const override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const CircleCollider* collider,
			const Transform& colliderTransform) const override;
		virtual CollisionPoints TestCollision(
			const Transform& transform,
			const DynamicCollider* collider,
			const Transform& colliderTransform) const override;
	};

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
			std::shared_ptr<Collider> _collider;
			bool _isTrigger;
			bool _isDynamic;
			std::function<void(Collision&, double)> _onCollision;
		public:
			CollisionObject(const Transform& t, std::shared_ptr<Collider> c, bool isTrigger);
			virtual ~CollisionObject();
			bool IsTrigger();
			bool IsDynamic();
			std::shared_ptr<Collider> GetCollider() const;
			geometry::Point GetPosition() const;
			geometry::Quaternion GetRotation() const;
			const Transform& GetTransform() const;
			const Transform& GetLastTransform() const;
			void SetCollider(Collider* c);
			void SetIsTrigger(bool b);
			void SetLastTransform(const Transform& t);
			void SetPosition(const geometry::Point& p);
			void SetRotation(const geometry::Quaternion& q);
			void SetTransform(const Transform& t);
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
			Rigidbody(const Transform& t, std::shared_ptr<Collider> c, bool isTrigger, double mass,
				bool usesGravity=true, double staticFriction=0.5, double dynamicFriction=0.5,
				double restitution=0.5);
			void ApplyForce(geometry::Vector f);
			double GetDynamicFriction() const;
			geometry::Vector GetForce() const;
			geometry::Vector GetGravity() const;
			double GetMass() const;
			double GetInvMass() const;
			double GetRestitution() const;
			double GetStaticFriction() const;
			geometry::Vector GetVelocity() const;
			void SetDynamicFriction(double f);
			void SetForce(const geometry::Vector& f);
			void SetGravity(const geometry::Vector& g);
			void SetMass(double m);
			void SetRestitution(double r);
			void SetStaticFriction(double f);
			void SetUsesGravity(bool b);
			void SetVelocity(const geometry::Vector& v);
			bool UsesGravity() const;
	};

	class Solver
	{
		public:
			virtual void Solve(std::vector<Collision>& collisions, double dt) = 0;
	};
}