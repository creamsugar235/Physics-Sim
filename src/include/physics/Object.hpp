#pragma once
#include "../geometry/main.hpp"
#include "../SFML/Graphics.hpp"
#include "Event.hpp"

namespace physics
{
	class Object;

	class Object : public geometry::Shape
	{
		protected:
			geometry::Point _scale;
			std::string _name;
			std::vector<Object*> collidedEntities;
			bool isColliding = false;
		public:
			Object();
			Object(std::string name, sf::Sprite s, double x, double y, bool isCircle=false);
			Object(std::string name, sf::Sprite s, double x, double y, std::vector<geometry::Point> points, bool isCircle=false);
			Object(const Object& o);
			virtual ~Object();
			virtual bool operator==(const Object& other) const noexcept;
			virtual bool operator!=(const Object& other) const noexcept;
			sf::Sprite sprite;
			std::vector<Object*> children;
			void AddChild(const Object& o);
			std::string GetName() const noexcept;
			geometry::Point GetScale() const noexcept;
			long GetHash() const noexcept;
			void SetName(const std::string& s);
			void SetScale(const geometry::Point& p);
			virtual void OnCollisionEnter(Object* o);
			virtual void OnCollisionStay(Object* o);
			virtual void OnCollisionExit(Object* o);
			bool IsColliding() const noexcept;
			std::vector<Object*> GetCollidedEntities() const noexcept;
			virtual void Start();
			virtual void Update();
			virtual void Destroy();
			Event<void(*)()> start;
			Event<void(*)()> update;
			Event<void(*)()> destroy;
	};
}