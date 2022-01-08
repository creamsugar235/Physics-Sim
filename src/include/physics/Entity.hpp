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
			CollisionObject* _collider;
			std::string _name;
			sf::Sprite _sprite;
			sf::Texture _texture;
			Transform _transform;
		public:
			Entity(const std::string& name, CollisionObject& c, const Transform& t, const sf::Sprite& s);
			Entity(const Entity& e);
			virtual ~Entity();
			virtual bool operator==(const Entity& other) const noexcept;
			virtual Entity* Clone() const noexcept;
			virtual CollisionObject& GetCollisionObject() const noexcept;
			std::string GetName() const noexcept;
			virtual sf::Sprite GetSprite() const noexcept;
			virtual Transform GetTransform() const noexcept;
			virtual void SetCollisionObject(CollisionObject& c);
			void SetName(const std::string& s);
			virtual void SetSprite(const sf::Sprite& s);
			virtual void SetTransform(const Transform& t);
			virtual void Update();
	};
}