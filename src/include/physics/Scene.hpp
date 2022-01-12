#pragma once
#include <fstream>
#include "Entity.hpp"
#include "Display.hpp"
#include "World.hpp"

namespace physics
{
	class Scene;
	struct Scene::Counter;
	struct SceneState
	{
		geometry::Vector _gravity;
		SmootherAccumulator = 0;
		Scene::Counter fpsCounter;
		Scene::Counter physicsUpdateCounter;
		double dt;
		bool debugDraw;
		std::vector<
	};


	class Scene
	{
		private:
			class PhysicsSmoothStepSystem final
			{
				private:
					double _accumulator = 0;
					Scene* _s = NULL;
				public:
					PhysicsSmoothStepSystem() noexcept;
					PhysicsSmoothStepSystem(Scene& s) noexcept;
					void Step(double dt) noexcept;
					void PhysicsUpdate() noexcept;
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
			std::vector<std::unique_ptr<Entity>> _entities;
			DynamicsWorld _world;
			geometry::Vector _gravity = geometry::Vector(0, -9.81);
			bool debugDraw;
		public:
			Scene(const geometry::Vector& gravity, double dt) noexcept;
			~Scene() noexcept;
			void SetGravity(const geometry::Vector& g) noexcept;
			void SetDt(double dt) noexcept;
			void AddEntity(Entity& e) noexcept;
			void RemoveEntity(Entity& e) noexcept;
			void Step(double dt) noexcept;
			double GetDt() const noexcept;
			const std::vector<std::unique_ptr<Entity>>& GetEntities() const noexcept;
			unsigned short physicsUpdateFrequency = 60;
			Display* display = NULL;
	};
}