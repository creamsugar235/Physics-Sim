#include "../include/physics/Entity.hpp"
#include <iostream>
namespace physics
{
	Entity::Entity(const std::string& name, CollisionObject& c, const Transform& t, const sf::Sprite& s) noexcept
	{
		_name = name;
		_collider = c.Clone();
		_sprite = s;
		_texture = *s.getTexture();
		_sprite.setTexture(_texture);
		_transform = t;
	}

	Entity::Entity(const Entity& e) noexcept
	{
		_name = e.GetName();
		_collider = e.GetCollisionObject().Clone();
		_sprite = e.GetSprite();
		_texture = *e.GetSprite().getTexture();
		_sprite.setTexture(_texture);
		_transform = e.GetTransform();
	}

	bool Entity::operator==(const Entity& other) const noexcept
	{
		return _name == other.GetName() && *_collider == other.GetCollisionObject() &&
		_transform == other.GetTransform();
	}

	bool Entity::operator!=(const Entity& other) const noexcept
	{
		return _name != other.GetName() || *_collider != other.GetCollisionObject() |
		_transform != other.GetTransform();
	}

	Entity::~Entity()
	{
		delete _collider;
	}

	Entity* Entity::Clone() const noexcept
	{
		return new Entity(*this);
	}

	CollisionObject& Entity::GetCollisionObject() const noexcept
	{
		return *_collider;
	}

	std::string Entity::GetName() const noexcept
	{
		return _name;
	}

	sf::Sprite Entity::GetSprite() const noexcept
	{
		//std::cout<<"IS MY SPRITE MESSED UP?"<<std::endl;
		return _sprite;
	}

	Transform Entity::GetTransform() const noexcept
	{
		return _transform;
	}

	void Entity::SetCollisionObject(CollisionObject& c) noexcept
	{
		delete _collider;
		_collider = c.Clone();
	}

	void Entity::SetName(const std::string& s) noexcept
	{
		_name = s;
	}

	void Entity::SetSprite(const sf::Sprite& s) noexcept
	{
		_sprite = s;
	}

	void Entity::SetTransform(const Transform& t) noexcept
	{
		_transform = t;
		_sprite.setPosition(t.position.x, t.position.y);
	}

	void Entity::Update() noexcept
	{
		_transform.position = _collider->GetTransform().position;
	}
}