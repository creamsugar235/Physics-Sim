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
		public:
			Object();
			Object(std::string name, sf::Texture* t, double x, double y, bool isCircle=false);
			Object(std::string name, sf::Texture* t, double x, double y, std::vector<geometry::Point> points, bool isCircle=false);
			Object(const Object& o);
			~Object();
			bool operator==(const Object& other) const;
			sf::Texture* texture = NULL;
			std::vector<Object*> children;
			void AddChild(const Object& o);
			std::string GetName() const;
			geometry::Point GetScale() const;
			long GetHash() const;
			void SetName(const std::string& s);
			void SetScale(const geometry::Point& p);
			Event<void(*)()> Start;
			Event<void(*)()> Update;
			Event<void(*)()> Destroy;
	};
}