#include "../include/physics/World.hpp"
#include <iostream>

namespace physics
{
	//bouncing
	void RestitutionSolver:: Solve(std::vector<Collision>& collisions, double dt)
	{
		for (Collision& c: collisions)
		{
			if (!c.a->IsDynamic() || !c.b->IsDynamic()) continue;
			Rigidbody* a = (Rigidbody*) c.a;
			Rigidbody* b = (Rigidbody*) c.b;
			double e = std::min(a->GetRestitution(), b->GetRestitution());
			geometry::Vector rv = b->GetVelocity() - a->GetVelocity();
			double velAlongNormal = rv.Dot(c.points.normal);
			if (velAlongNormal > 0) continue;
			double j = -(1 + e) * velAlongNormal;
			j /= a->GetInvMass() + b->GetInvMass();
			geometry::Vector impulse = c.points.normal * j;
			geometry::Vector aVel = a->GetVelocity();
			geometry::Vector bVel = b->GetVelocity();
			aVel -= impulse * a->GetInvMass();
			bVel -= impulse * b->GetInvMass();
			a->SetVelocity(aVel);
			b->SetVelocity(bVel);
		}
	}

	template <typename T>
	T getMin(std::vector<T>& v)	
	{
		bool reachedVal = false;
		T minVal;
		for (T item: v)
		{
			if (!reachedVal)
			{
				minVal = item; reachedVal = true; continue;
			}
			if (minVal > item)
			{
				minVal = item;
			}
		}
		return minVal;
	}

	template <typename T>
	T getMax(std::vector<T>& v)	
	{
		bool reachedVal = false;
		T maxVal;
		for (T item: v)
		{
			if (!reachedVal)
			{
				maxVal = item; reachedVal = true; continue;
			}
			if (maxVal < item)
			{
				maxVal = item;
			}
		}
		return maxVal;
	}

	struct Square
	{
		double x = 0;
		double y = 0;
		double width = 0;
		double height = 0;
	};

	bool SquareOverLaps(const Square& a, const Square& b)
	{
		if (a.x >= b.x + b.width || b.x >= a.x + a.width)
			return false;
		if (a.y + a.height >= b.y || b.y + b.height >= a.y)
			return false;
		return true;
	}

	void CollisionWorld::AddObject(CollisionObject* o)
	{
		_objects.emplace_back(o);
	}

	void CollisionWorld::AddSolver(Solver* s)
	{
		_solvers.emplace_back(s);
	}

	void CollisionWorld::ResolveCollisions(double dt)
	{
		std::vector<Collision> collisions;
		for (auto& a: _objects)
		{
			for (auto& b: _objects)
			{
				if (a == b) break;
				Square BoundingBoxA;
				Square BoundingBoxB;
				auto clone = a->GetCollider().Clone();
				if (dynamic_cast<CircleCollider*>(clone))
				{
					CircleCollider& cc = dynamic_cast<CircleCollider&>(a->GetCollider());
					geometry::Point center = cc.center;
					double radius = cc.radius;
					BoundingBoxA.x = center.x - radius;
					BoundingBoxA.y = center.y - radius;
					BoundingBoxA.width = radius * 2;
					BoundingBoxA.height = radius * 2;
				}
				else if (dynamic_cast<DynamicCollider*>(clone))
				{
					DynamicCollider& dc = dynamic_cast<DynamicCollider&>(a->GetCollider());
					geometry::Point minimum = getMin(dc.points);
					geometry::Point maximum = getMax(dc.points);
					BoundingBoxA.x = minimum.x;
					BoundingBoxA.y = minimum.y;
					BoundingBoxA.width = maximum.x - minimum.x;
					BoundingBoxA.height = maximum.y - minimum.y;
				}
				delete clone;
				clone = b->GetCollider().Clone();
				if (dynamic_cast<CircleCollider*>(clone))
				{
					CircleCollider& cc = dynamic_cast<CircleCollider&>(b->GetCollider());
					geometry::Point center = cc.center;
					double radius = cc.radius;
					BoundingBoxB.x = center.x - radius;
					BoundingBoxB.y = center.y - radius;
					BoundingBoxB.width = radius * 2;
					BoundingBoxB.height = radius * 2;
				}
				else if (dynamic_cast<DynamicCollider*>(clone))
				{
					DynamicCollider& dc = dynamic_cast<DynamicCollider&>(b->GetCollider());
					geometry::Point minimum = getMin(dc.points);
					geometry::Point maximum = getMax(dc.points);
					BoundingBoxB.x = minimum.x;
					BoundingBoxB.y = minimum.y;
					BoundingBoxB.width = maximum.x - minimum.x;
					BoundingBoxB.height = maximum.y - minimum.y;
				}
				delete clone;
				if (SquareOverLaps(BoundingBoxA, BoundingBoxB))
				{
					std::cout<<"OMG WE TOUCHED?"<<std::endl;
					CollisionPoints points = a->GetCollider().TestCollision(
						a->GetTransform(), &b->GetCollider(), b->GetTransform()
					);
					if (points.hasCollision)
					{
						std::cout<<"WE DIDDD!!"<<std::endl;
						Collision c;
						c.a = a;
						c.b = b;
						c.points = points;
						collisions.push_back(c);
					}
				}
			}
		}
		for (auto solver: _solvers)
		{
			solver->Solve(collisions, dt);
		}
	}

	void CollisionWorld::RemoveObject(CollisionObject* o)
	{
		for (auto p = _objects.begin(); p < _objects.end(); p++)	
		{
			if (*p == o)
			{
				_objects.erase(p);
				return;
			}
		}
	}

	void CollisionWorld::RemoveSolver(Solver* s)
	{
		for (auto p = _solvers.begin(); p < _solvers.end(); p++)
		{
			if (*p == s)
			{
				_solvers.erase(p);
				return;
			}
		}
	}

	void CollisionWorld::SetCollisionCallBack(std::function<void(Collision&, double)>& callback, double dt)
	{
		_onCollision = callback;
	}

	void CollisionWorld::SendCollisionCallBacks(std::vector<Collision>& collisions, double dt)
	{
		for (Collision& c : collisions)
		{
			_onCollision(c, dt);
			/*auto& a = c.a->OnCollision();
			auto& b = c.b->OnCollision();
			if (a) a(c, dt);
			if (b) b(c, dt);*/
		}
	}

	void DynamicsWorld::AddRigidbody(Rigidbody* r)
	{
		if (r->UsesGravity())
		{
			r->SetGravity(_gravity);
		}
		_objects.emplace_back(r);
	}

	void DynamicsWorld::ApplyGravity()
	{
		for (auto& obj: _objects)
		{
			if (!obj->IsDynamic()) continue;
			Rigidbody* rigidbody = (Rigidbody*) obj;
			rigidbody->ApplyForce(rigidbody->GetGravity() * rigidbody->GetMass());
		}
	}

	void DynamicsWorld::MoveObjects(double dt)
	{
		for (auto& obj: _objects)
		{
			if (!obj->IsDynamic()) continue;
			Rigidbody* rigidbody = (Rigidbody*)obj;
			geometry::Vector vel = rigidbody->GetVelocity()
			+ (rigidbody->GetForce() / rigidbody->GetMass() * dt);
			rigidbody->SetVelocity(vel);
			geometry::Vector pos = geometry::Vector(rigidbody->GetPosition()) + rigidbody->GetVelocity() * dt;
			rigidbody->SetPosition(pos);
			rigidbody->SetForce(geometry::Vector(0, 0));
		}
	}

	void DynamicsWorld::Update(double dt)
	{
		ApplyGravity();
		ResolveCollisions(dt);
		MoveObjects(dt);
	}
}