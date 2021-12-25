#include "../include/physics/Object.hpp"
#include "../include/physics/Event.hpp"

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

	bool Object::operator==(const Object& o) const
	{
		return GetHash() == o.GetHash();
	}

	void Object::AddChild(const Object& o)
	{
		children.emplace_back(new Object(o));
	}

	std::string Object::GetName() const
	{
		return _name;
	}

	geometry::Point Object::GetScale() const
	{
		return _scale;
	}

	long Object::GetHash() const
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
}