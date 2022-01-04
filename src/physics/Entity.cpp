#include "../include/physics/Entity.hpp"
namespace physics
{
	Entity::Entity(const std::string& name, std::shared_ptr<CollisionObject> c, const Transform& t, const sf::Sprite& s)
	{
		_name = name;
		_collider = c;
		_sprite = s;
		_transform = t;
	}

	Entity::~Entity()
	{
	}

	std::shared_ptr<CollisionObject> Entity::GetCollisionObject() const noexcept
	{
		return _collider;
	}

	std::string Entity::GetName() const noexcept
	{
		return _name;
	}

	sf::Sprite Entity::GetSprite() const noexcept
	{
		return _sprite;
	}

	Transform Entity::GetTransform() const noexcept
	{
		return _transform;
	}

	void Entity::SetCollisionObject(std::shared_ptr<CollisionObject> c)
	{
		_collider = c;
	}

	void Entity::SetName(const std::string& s)
	{
		_name = s;
	}

	void Entity::SetSprite(const sf::Sprite& s)
	{
		_sprite = s;
	}

	void Entity::SetTransform(const Transform& t)
	{
		_transform = t;
		_sprite.setPosition(t.position.x, t.position.y);
	}
}