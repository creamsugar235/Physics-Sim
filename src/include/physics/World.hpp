#pragma once
#include "Object.hpp"
#include "Collision.hpp"

namespace physics
{
	class RestitutionSolver : Solver
	{
		public:
			void Solve(std::vector<Collision>& collisions, double dt) override;
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
			void AddObject(CollisionObject* o);
			void AddSolver(Solver* s);
			void ResolveCollisions(double dt);
			void RemoveObject(CollisionObject* o);
			void RemoveSolver(Solver* s);
			void SetCollisionCallBack(std::function<void(Collision&, double)>& callback, double dt);
			void SendCollisionCallBacks(std::vector<Collision>& collisions, double dt);
	};

	class DynamicsWorld : public CollisionWorld
	{
		private:
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
		public:
			void AddRigidbody(Rigidbody* rb);
			void ApplyGravity();
			void MoveObjects(double dt);
			void Update(double dt);
	};
}