#include "../include/physics/World.hpp"

namespace physics
{
	template <typename T>
	T getMin(std::vector<T>& v)	
	{
		bool reachedVal = false;
		T minVal;
		for (T item: v)
		{
			if (!reachedVal)
				minVal = item; reachedVal = true; continue;
			if (minVal > item)
				minVal = item;
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
				maxVal = item; reachedVal = true; continue;
			if (maxVal < item)
				maxVal = item;
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
		for (CollisionObject* a: _objects)
		{
			for (CollisionObject* b: _objects)
			{
				if (a == b) break;
				if (!a->GetCollider() || !b->GetCollider())
				{
					continue;
				}
				Square BoundingBoxA;
				Square BoundingBoxB;
				if (dynamic_cast<CircleCollider*>(a->GetCollider()))
				{
					CircleCollider* cc = dynamic_cast<CircleCollider*>(a->GetCollider());
					geometry::Point center = cc->center;
					double radius = cc->radius;
					BoundingBoxA.x = center.x - radius;
					BoundingBoxA.y = center.y - radius;
					BoundingBoxA.width = radius * 2;
					BoundingBoxA.height = radius * 2;
				}
				else if (dynamic_cast<DynamicCollider*>(a->GetCollider()))
				{
					DynamicCollider* dc = dynamic_cast<DynamicCollider*>(a->GetCollider());
					geometry::Point minimum = getMin(dc->points);
					geometry::Point maximum = getMax(dc->points);
					BoundingBoxA.x = minimum.x;
					BoundingBoxA.y = minimum.y;
					BoundingBoxA.width = maximum.x - minimum.x;
					BoundingBoxA.height = maximum.y - minimum.y;
				}
				if (dynamic_cast<CircleCollider*>(b->GetCollider()))
				{
					CircleCollider* cc = dynamic_cast<CircleCollider*>(b->GetCollider());
					geometry::Point center = cc->center;
					double radius = cc->radius;
					BoundingBoxB.x = center.x - radius;
					BoundingBoxB.y = center.y - radius;
					BoundingBoxB.width = radius * 2;
					BoundingBoxB.height = radius * 2;
				}
				else if (dynamic_cast<DynamicCollider*>(b->GetCollider()))
				{
					DynamicCollider* dc = dynamic_cast<DynamicCollider*>(b->GetCollider());
					geometry::Point minimum = getMin(dc->points);
					geometry::Point maximum = getMax(dc->points);
					BoundingBoxB.x = minimum.x;
					BoundingBoxB.y = minimum.y;
					BoundingBoxB.width = maximum.x - minimum.x;
					BoundingBoxB.height = maximum.y - minimum.y;
				}
				if (SquareOverLaps(BoundingBoxA, BoundingBoxB))
				{
					CollisionPoints points = a->GetCollider()->TestCollision(
						a->GetTransform(), b->GetCollider(), b->GetTransform()
					);
					if (points.hasCollision)
					{
						Collision c;
						c.a = a;
						c.b = b;
						c.points = points;
						collisions.push_back(c);
					}
				}
			}
		}
		for (Solver* solver: _solvers)
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

	void CollisionWorld::SetCollisionCallBack(std::function<void(Collision&, double)>& callback)
	{
		_onCollision = callback;
	}

	void CollisionWorld::SendCollisionCallbacks(std::vector<Collision>& collisions,
		double dt)
	{
		for (Collision& c : collisions)
		{
			_onCollision(collision, dt);
			auto& a = collision.a->OnCollision();
			auto& b = collision.b->OnCollision();
			if (a) a(collision, dt);
			if (b) b(collision, dt);
		}
	}

	void DynamicsWorld::AddRigidbody(Rigidbody* r)
	{
		if (r->UsesGravity())
		{
			r->SetGravity(_gravity);
		}
	}

	void DynamicsWorld::ApplyGravity()
	{
		for (CollisionObject* obj: _objects)
		{
			if (!obj->IsDynamic()) continue;
			Rigidbody* rigidbody = (Rigidbody*) obj;
			rigidbody->ApplyForce(rigidbody->GetGravity() * rigidbody->GetMass());
		}
	}

	void DynamicsWorld::MoveObjects(double dt)
	{
		for (CollisionObject* obj: _objects)
		{
			if !(objects->IsDynamic()) continue;
			Rigidbody* rigidbody = (Rigidbody*)obj;
			geometry::Vector vel = rigidbody->GetVelocity()
			+ rigidbody->GetForce() / rigidbody->GetMass() * dt;
			rigidbody->SetVelocity(vel);
			geometry::Vector pos = rigidbody->GetPosition() + rigidbody->Velocity() * dt;
			rigidbody->SetPosition(pos);
			rigidbody->SetForce(geometry::Vector(0, 0, 0));
		}
	}

	void DynamicsWorld::Update(doube dt)
	{
		ApplyGravity();
		ResolveCollisions(dt);
		MoveObjects(dt);
	}
}