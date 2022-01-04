#pragma once
#include "Entity.hpp"
#include "Display.hpp"
#include "World.hpp"

namespace physics
{
	class Scene;
	class Scene
	{
		private:
			class PhysicsSmoothStepSystem final
			{
				private:
					double _accumulator = 0;
					Scene* _s = NULL;
				public:
					PhysicsSmoothStepSystem();
					PhysicsSmoothStepSystem(Scene& s);
					void Step(double dt);
					void PhysicsUpdate();
					double physicsUpdateRate;
			};

			struct Counter final
			{
				unsigned int loops;
				double total;
				std::vector<double> loopsPerSecond;
			};

			Counter _fpsCounter;
			Counter _physicsUpdateCounter;
			PhysicsSmoothStepSystem _smoother;
			double _dt;
			std::vector<std::shared_ptr<Entity>> _entities;
			DynamicsWorld _world;
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
			bool debugDraw;
		public:
			Scene(const geometry::Vector& gravity, double dt);
			~Scene();
			void SetGravity(const geometry::Vector& g);
			void SetDt(double dt);
			std::shared_ptr<Entity> CreateEntity(const std::string& name, std::shared_ptr<CollisionObject> c, const Transform& t, const sf::Sprite& s);
			void AddEntity(std::shared_ptr<Entity> e);
			void Step(double dt);
			double GetDt() const;
			std::vector<std::shared_ptr<Entity>> GetEntities() const;
			unsigned short physicsUpdateFrequency = 60;
			Display* display = NULL;
	};
}