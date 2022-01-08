#include "../include/physics/Entity.hpp"
#include <iostream>
namespace physics
{
	Entity::Entity(const std::string& name, CollisionObject& c, const Transform& t, const sf::Sprite& s)
	{
		_name = name;
		_collider = c.Clone();
		_sprite = s;
		_texture = *s.getTexture();
		_sprite.setTexture(_texture);
		_transform = t;
	}

	Entity::Entity(const Entity& e)
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
		return true;
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

	void Entity::SetCollisionObject(CollisionObject& c)
	{
		delete _collider;
		_collider = c.Clone();
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

	void Entity::Update()
	{
		_transform.position = _collider->GetTransform().position;
	}
}