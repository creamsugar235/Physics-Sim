#pragma once
#include "Collision.hpp"

namespace physics
{
	class Solver
	{
		public:
			virtual void Solve(std::vector<Collision>& collisions, double dt) noexcept = 0;
	};
	class RestitutionSolver : Solver
	{
		public:
			void Solve(std::vector<Collision>& collisions, double dt) noexcept override;
	};
	
	class DynamicsWorld;
	class CollisionWorld;
	class CollisionWorld
	{
		protected:
			std::vector<CollisionObject*> _objects;
			std::vector<Solver*> _solvers;
			std::function<void(Collision&, double)> _onCollision;
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
		public:
			void AddObject(CollisionObject* o) noexcept;
			void AddSolver(Solver* s) noexcept;
			void ResolveCollisions(double dt) noexcept;
			void RemoveObject(CollisionObject* o) noexcept;
			void RemoveSolver(Solver* s) noexcept;
			void SetCollisionCallBack(std::function<void(Collision&, double)>& callback, double dt) noexcept;
			void SendCollisionCallBacks(std::vector<Collision>& collisions, double dt) noexcept;
	};

	class DynamicsWorld : public CollisionWorld
	{
		private:
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
		public:
			void AddRigidbody(Rigidbody* rb) noexcept;
			void ApplyGravity() noexcept;
			void MoveObjects(double dt) noexcept;
			void Update(double dt) noexcept;
	};
}