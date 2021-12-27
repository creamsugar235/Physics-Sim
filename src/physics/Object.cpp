#include "../include/physics/Object.hpp"
#include "../include/physics/Event.hpp"
#include "../include/physics/Global.hpp"
#include <iostream>

namespace physics
{
	Object::Object() : geometry::Shape()
	{
	}

	Object::Object(std::string name, sf::Sprite s, double x, double y, bool isCircle)
	: geometry::Shape(x, y, isCircle)
	{
		_name = name;
		sprite = s;
		sprite.setPosition(x, y);
	}

	Object::Object(std::string name, sf::Sprite s, double x, double y, std::vector<geometry::Point> points, bool isCircle)
	: geometry::Shape(x, y, points, isCircle)
	{
		_name = name;
		sprite = s;
		sprite.setPosition(x, y);
	}

	Object::Object(const Object& o) : geometry::Shape((geometry::Shape)o)
	{
		_name = o.GetName();
		sprite = o.sprite;
	}

	Object::~Object()
	{
		for (auto& p: children)
		{
			delete p;
		}
	}

	bool Object::operator==(const Object& o) const noexcept
	{
		return GetHash() == o.GetHash();
	}

	bool Object::operator!=(const Object& o) const noexcept
	{
		return GetHash() != o.GetHash();
	}

	void Object::AddChild(const Object& o)
	{
		children.emplace_back(new Object(o));
	}

	std::string Object::GetName() const noexcept
	{
		return _name;
	}

	geometry::Point Object::GetScale() const noexcept
	{
		return _scale;
	}

	long Object::GetHash() const noexcept
	{
		if (!this->_points.size())
		{
			return 0;
		}
		std::string s = "";
		for (geometry::Point p: this->_points)
		{
			s = s + ", " + p.ToString();
		}
		int h = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			h = h * 31 + static_cast<int>(s[i]);
		}
		return h;
	}

	void Object::SetName(const std::string& s)
	{
		_name = s;
	}

	void Object::SetScale(const geometry::Point& p)
	{
		_scale = p;
		sprite.setScale(p.x, p.y);
	}

	void Object::OnCollisionEnter(Object* o)
	{
		std::cout<<"ENTER"<<std::endl;
		isColliding = true;
		collidedEntities.push_back(o);
	}

	void Object::OnCollisionStay(Object* o)
	{
		std::cout<<"STAY"<<std::endl;
		isColliding = true;
	}

	void Object::OnCollisionExit(Object* o)
	{
		std::cout<<"EXIT"<<std::endl;
		for (auto p = collidedEntities.begin(); p < collidedEntities.end(); p++)
		{
			if (**p == *o)
			{
				collidedEntities.erase(p);
				break;
			}
		}
		isColliding = (collidedEntities.size() != 0);
	}

	bool Object::IsColliding() const noexcept
	{
		return isColliding;
	}

	std::vector<Object*> Object::GetCollidedEntities() const noexcept
	{
		return collidedEntities;
	}

	void Object::Start()
	{
		start();
	}

	void Object::Update()
	{
		isColliding = (collidedEntities.size() != 0);
		if (isColliding)
		{
			sprite.setTexture(textures["circle_hit"]);
		}
		if (!isColliding)
		{
			sprite.setTexture(textures["circle"]);
		}
		Move(_vector.direction.x, _vector.direction.y);
		update();
	}

	void Object::Destroy()
	{
		destroy();
	}
}