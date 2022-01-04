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
			std::vector<std::shared_ptr<CollisionObject>> _objects;
			std::vector<std::shared_ptr<Solver>> _solvers;
			std::function<void(Collision&, double)> _onCollision;
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
		public:
			void AddObject(std::shared_ptr<CollisionObject> o);
			void AddSolver(std::shared_ptr<Solver> s);
			void ResolveCollisions(double dt);
			void RemoveObject(std::shared_ptr<CollisionObject> o);
			void RemoveSolver(std::shared_ptr<Solver> s);
			void SetCollisionCallBack(std::function<void(Collision&, double)>& callback, double dt);
			void SendCollisionCallBacks(std::vector<Collision>& collisions, double dt);
	};

	class DynamicsWorld : public CollisionWorld
	{
		private:
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
		public:
			void AddRigidbody(std::shared_ptr<Rigidbody> rb);
			void ApplyGravity();
			void MoveObjects(double dt);
			void Update(double dt);
	};
}