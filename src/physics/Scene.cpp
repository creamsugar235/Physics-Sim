#include "../include/physics/Scene.hpp"
#include <iostream>

namespace physics
{
	Scene::PhysicsSmoothStepSystem::PhysicsSmoothStepSystem(Scene& s)
	{
		_s = &s;
	}

	Scene::PhysicsSmoothStepSystem::PhysicsSmoothStepSystem()
	{
	}

	void Scene::PhysicsSmoothStepSystem::Step(double dt)
	{
		auto lerp = [&](geometry::Vector a, geometry::Vector b, double t){
			auto clamp = [&](double d){
				if (d < 0)
					return 0.0;
				else if (d > 1)
					return 1.0;
				else
					return d;
			};
			t = clamp(t);
			return geometry::Vector(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
		};
		for (auto& ptr: _s->GetEntities())
		{
			Transform t = ptr->GetCollisionObject().GetTransform();
			CollisionObject& object = ptr->GetCollisionObject();
			Transform last = object.GetLastTransform();
			Transform current = object.GetTransform();
			t.position = lerp(geometry::Vector(last.position), geometry::Vector(current.position), _accumulator / _s->physicsUpdateFrequency);
			object.SetTransform(t);
		}
		_accumulator += dt;
	}

	void Scene::PhysicsSmoothStepSystem::PhysicsUpdate()
	{
		_accumulator = 0;
	}

	Scene::Scene(const geometry::Vector& gravity, double dt)
	{
		_smoother = PhysicsSmoothStepSystem(*this);
		_gravity = gravity;
		_dt = dt;
		std::string name = "display";
		display = new Display(500, 500, name);
	}

	Scene::~Scene()
	{
		delete display;
	}

	const std::vector<std::unique_ptr<Entity>>& Scene::GetEntities() const
	{
		return _entities;
	}

	void Scene::AddEntity(Entity& e)
	{
		std::unique_ptr<Entity> ptr(e.Clone());
		if (ptr->GetCollisionObject().IsDynamic())
		{
			_world.AddRigidbody(dynamic_cast<Rigidbody*>(&ptr->GetCollisionObject()));
		}
		else
		{
			_world.AddObject(&ptr->GetCollisionObject());
		}
		_entities.emplace_back(ptr.release());
	}

	void Scene::RemoveEntity(Entity& e)
	{
		size_t ind;
		for (auto& ptr: _entities)
		{
			if (*ptr == e)
			{
				_world.RemoveObject(&ptr->GetCollisionObject());
				_entities.erase(_entities.begin() + ind);
				return;
			}
			ind++;
		}
	}

	void Scene::Step(double dt)
	{
		if (dt + _fpsCounter.total > 1000)
		{
			if (_fpsCounter.loopsPerSecond.size() > 60)
				_fpsCounter.loopsPerSecond.clear();
			_fpsCounter.loopsPerSecond.push_back((double)_fpsCounter.loops);
			_fpsCounter.total = dt;
			_fpsCounter.loops = 0;
		}
		else
		{
			_fpsCounter.total += dt;
			_fpsCounter.loops++;
		}
		if (physicsUpdateFrequency)
		{
			if (dt + _physicsUpdateCounter.total > 1000 / physicsUpdateFrequency)
			{
				_world.Update(_physicsUpdateCounter.total + dt);
				_physicsUpdateCounter.total = 0;
			}
			else
			{
				_physicsUpdateCounter.total += dt;
			}
		}
	}
}