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
			Transform t = ptr->GetCollisionObject()->GetTransform();
			CollisionObject* object = ptr->GetCollisionObject().get();
			Transform last = object->GetLastTransform();
			Transform current = object->GetTransform();
			t.position = lerp(geometry::Vector(last.position), geometry::Vector(current.position), _accumulator / _s->physicsUpdateFrequency);
			object->SetTransform(t);
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

	std::shared_ptr<Entity> Scene::CreateEntity(const std::string& name, std::shared_ptr<CollisionObject> c, const Transform& t, const sf::Sprite& s)
	{
		Entity* E = new Entity(name, c, t, s);
		return std::shared_ptr<Entity>(E);
	}

	std::vector<std::shared_ptr<Entity>> Scene::GetEntities() const
	{
		return _entities;
	}

	void Scene::AddEntity(std::shared_ptr<Entity> e)
	{
		_entities.emplace_back(e);
		if (e->GetCollisionObject()->IsDynamic())
		{
			_world.AddRigidbody(std::shared_ptr<Rigidbody>(dynamic_cast<Rigidbody*>(e->GetCollisionObject().get())));
		}
		else
		{
			_world.AddObject(e->GetCollisionObject());
		}
	}

	void Scene::Step(double dt)
	{
		if (dt + _fpsCounter.total > 1000)
		{
			std::cout<<"UPDAtE!!"<<std::endl;
			if (_fpsCounter.loopsPerSecond.size() > 60)
				_fpsCounter.loopsPerSecond.clear();
			_fpsCounter.loopsPerSecond.push_back(_fpsCounter.loops);
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
		else
		{
			_world.Update(dt);
		}
	}
}