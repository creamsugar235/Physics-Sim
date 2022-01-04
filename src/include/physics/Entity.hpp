#pragma once
#include "../SFML/Graphics.hpp"
#include "Collision.hpp"
#include "Object.hpp"
#include <memory>

namespace physics
{
	class Entity
	{
		private:
			std::shared_ptr<CollisionObject> _collider;
			std::string _name;
			sf::Sprite _sprite;
			Transform _transform;
		public:
			Entity(const std::string& name, std::shared_ptr<CollisionObject> c, const Transform& t, const sf::Sprite& s);
			Entity(const Entity& e);
			virtual ~Entity();
			virtual std::shared_ptr<CollisionObject> GetCollisionObject() const noexcept;
			std::string GetName() const noexcept;
			virtual sf::Sprite GetSprite() const noexcept;
			virtual Transform GetTransform() const noexcept;
			virtual void SetCollisionObject(std::shared_ptr<CollisionObject> c);
			void SetName(const std::string& s);
			virtual void SetSprite(const sf::Sprite& s);
			virtual void SetTransform(const Transform& t);
	};
}