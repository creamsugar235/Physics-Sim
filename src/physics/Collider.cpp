#include "../include/physics/Collider.hpp"

namespace physics
{
	std::vector<unsigned char> Transform::Serialize() const
	{
		std::vector<unsigned char> v;
		if (IS_BIG_ENDIAN)
		{
			const unsigned char* c = (const unsigned char*)&position.x;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[i]);
			c = (const unsigned char*)&position.y;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[i]);
			c = (const unsigned char*)&scale.x;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[i]);
			c = (const unsigned char*)&scale.y;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[i]);
			c = (const unsigned char*)&rotation;
			for (unsigned i = 0; i < sizeof(rotation); i++)
				v.push_back(c[i]);
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		else
		{
			const unsigned char* c = (const unsigned char*)&position.x;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[sizeof(double) - 1 - i]);
			c = (const unsigned char*)&position.y;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[sizeof(double) - 1 -i]);
			c = (const unsigned char*)&scale.x;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[sizeof(double) - 1 - i]);
			c = (const unsigned char*)&scale.y;
			for (unsigned i = 0; i < sizeof(double); i++)
				v.push_back(c[sizeof(double) - 1 - i]);
			c = (const unsigned char*)&rotation;
			for (unsigned i = 0; i < sizeof(rotation); i++)
				v.push_back(c[sizeof(rotation) - 1 -i]);
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		return v;
	}

	const unsigned long Transform::TotalByteSize() const noexcept
	{
		return sizeof(double) * 4 + sizeof(rotation) + 3; // +3 for end of object
	}

	serialization::Serializable* Transform::Deserialize(std::vector<unsigned char> v) const
	{
		if (v.size() < TotalByteSize())
		{
			throw std::runtime_error("Insufficient amount of bytes for deserialization. ");
		}
		auto iter = v.begin();
		Transform* t = new Transform;
		double posX = 0;
		double posY = 0;
		double scaleX = 0;
		double scaleY = 0;
		geometry::Quaternion rot;
		if (BIG_ENDIAN)
		{
			unsigned char* c = (unsigned char* )&posX;
			for (unsigned i = 0;i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char* )&posY;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char* )&scaleX;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char* )&scaleY;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&rot;
			for (unsigned i = 0; i < sizeof(geometry::Quaternion); i++)
			{
				c[i] = *iter;
				iter++;
			}
		}
		else
		{
			unsigned char* c = (unsigned char* )&posX;
			for (unsigned i = 0;i < sizeof(double); i++)
			{
				c[sizeof(double) - 1 - i] = *iter;
				iter++;
			}
			c = (unsigned char* )&posY;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[sizeof(double) - 1 - i] = *iter;
				iter++;
			}
			c = (unsigned char* )&scaleX;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[sizeof(double) - 1 -i] = *iter;
				iter++;
			}
			c = (unsigned char* )&scaleY;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[sizeof(double) - 1- i] = *iter;
				iter++;
			}
			c = (unsigned char*)&rot;
			for (unsigned i = 0; i < sizeof(geometry::Quaternion); i++)
			{
				c[sizeof(geometry::Quaternion) - 1 - i] = *iter;
				iter++;
			}
		}
		t->position.x = posX;
		t->position.y = posY;
		t->scale.x = scaleX;
		t->scale.y = scaleY;
		t->rotation = rot;
		return t;
	}

	DynamicCollider::DynamicCollider(const DynamicCollider& d) noexcept
	{
		this->pos = d.pos;
		this->points = d.points;
		classCode = 0x04;
	}

	DynamicCollider::DynamicCollider()
	{
		classCode = 0x04;
	}

	DynamicCollider::DynamicCollider(geometry::Vector pos,
		geometry::Vector a,
		geometry::Vector b,
		geometry::Vector c,
		std::initializer_list<geometry::Vector> extra) noexcept
	{
		classCode = 0x04;
		this->pos = pos;
		points = {extra};
		points.insert(points.begin(), c);
		points.insert(points.begin(), b);
		points.insert(points.begin(), a);
	}

	bool DynamicCollider::operator==(const Collider& other) const noexcept
	{
		DynamicCollider tmp;
		try
		{
			tmp = dynamic_cast<const DynamicCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return false;
		}
		return pos == tmp.pos && points == tmp.points;
	}

	bool DynamicCollider::operator!=(const Collider& other) const noexcept
	{
		DynamicCollider tmp;
		try
		{
			tmp = dynamic_cast<const DynamicCollider&>(other);
		}
		catch (const std::bad_cast& e)
		{
			return true;
		}
		return pos != tmp.pos || points != tmp.points;
	}

	std::vector<unsigned char> DynamicCollider::Serialize() const
	{
		std::vector<unsigned char> v;
		if (BIG_ENDIAN)
		{
			const unsigned char* c = (const unsigned char*)&pos.x;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				v.push_back(c[i]);
			}
			c = (const unsigned char*)&pos.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				v.push_back(c[i]);
			}
			double d = v.size();
			c = (const unsigned char*)&d;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				v.push_back(c[i]);
			}
			for (const geometry::Vector& vec: points)
			{
				c = (const unsigned char*)&vec.x;
				for (unsigned i = 0; i < sizeof(double); i++)
				{
					v.push_back(c[i]);
				}
				c = (const unsigned char*)&vec.y;
				for (unsigned i = 0; i < sizeof(double); i++)
				{
					v.push_back(c[i]);
				}
			}
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		else
		{
			const unsigned char* c = (const unsigned char*)&pos.x;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				v.push_back(c[sizeof(double) - 1 - i]);
			}
			c = (const unsigned char*)&pos.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				v.push_back(c[sizeof(double) - 1 - i]);
			}
			double d = v.size();
			c = (const unsigned char*)&d;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				v.push_back(c[sizeof(double) - 1 - i]);
			}
			for (const geometry::Vector& vec: points)
			{
				c = (const unsigned char*)&vec.x;
				for (unsigned i = 0; i < sizeof(double); i++)
				{
					v.push_back(c[sizeof(double) - 1 - i]);
				}
				c = (const unsigned char*)&vec.y;
				for (unsigned i = 0; i < sizeof(double); i++)
				{
					v.push_back(c[sizeof(double) - 1 - i]);
				}
			}
			v.push_back(0xff);
			v.push_back(0xff);
			v.push_back(0xff);
		}
		return v;
	}
	serialization::Serializable* DynamicCollider::Deserialize(std::vector<unsigned char> v) const
	{
		DynamicCollider* d = new DynamicCollider();
		if (BIG_ENDIAN)
		{
			auto iter = v.begin();
			unsigned char* c = (unsigned char*)&d->pos.x;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&d->pos.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			double size = 0;
			c = (unsigned char*)&size;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			for (unsigned i = 0; i < size; i++)
			{
				geometry::Vector tmp;
				c = (unsigned char*)&tmp.x;
				for (unsigned j = 0; j < sizeof(double); j++)
				{
					c[j] = *iter;
					iter++;
				}
				c = (unsigned char*)&tmp.y;
				for (unsigned j = 0; j < sizeof(double); j++)
				{
					c[j] = *iter;
					iter++;
				}
				d->points.push_back(tmp);
			}
		}
		else
		{
			auto iter = v.begin();
			unsigned char* c = (unsigned char*)&d->pos.x;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[sizeof(double) - 1 - i] = *iter;
				iter++;
			}
			c = (unsigned char*)&d->pos.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[sizeof(double) - 1 - i] = *iter;
				iter++;
			}
			double size = 0;
			c = (unsigned char*)&size;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[sizeof(double) - 1 - i] = *iter;
				iter++;
			}
			for (unsigned i = 0; i < size; i++)
			{
				geometry::Vector tmp;
				c = (unsigned char*)&tmp.x;
				for (unsigned j = 0; j < sizeof(double); j++)
				{
					c[sizeof(double) - 1 - j] = *iter;
					iter++;
				}
				c = (unsigned char*)&tmp.y;
				for (unsigned j = 0; j < sizeof(double); j++)
				{
					c[sizeof(double) - 1 - j] = *iter;
					iter++;
				}
				d->points.push_back(tmp);
			}
		}
		return d;
	}

	const unsigned long DynamicCollider::TotalByteSize() const noexcept
	{
		return (sizeof(double) * 2) + (points.size() * sizeof(double)) + 4;
	}

	Collider::~Collider()
	{
	}


	Collider* DynamicCollider::Clone() const
	{
		return new DynamicCollider(*this);
	}

	CircleCollider::CircleCollider(geometry::Vector center, double radius)
	{
		classCode = 0x03;
		this->center = center;
		this->radius = fabs(radius);
	}

	CircleCollider::CircleCollider() {classCode = 0x03;}

	CircleCollider::CircleCollider(const CircleCollider& c)
	{
		classCode = 0x03;
		this->radius = c.radius;
		this->center = c.center;
	}

	Collider* CircleCollider::Clone() const
	{
		return new CircleCollider(*this);
	}

	bool CircleCollider::operator==(const Collider& other) const noexcept
	{
		CircleCollider tmp = CircleCollider(geometry::Vector(0, 0), 0);
		try
		{
			CircleCollider tmp = dynamic_cast<const CircleCollider&>(other);
		}
		catch(const std::bad_cast	& c)
		{
			return false;
		}
		return tmp.radius == radius && tmp.center == center;
	}

	bool CircleCollider::operator!=(const Collider& other) const noexcept
	{
		CircleCollider tmp = CircleCollider(geometry::Vector(0, 0), 0);
		try
		{
			CircleCollider tmp = dynamic_cast<const CircleCollider&>(other);
		}
		catch(const std::bad_cast& c)
		{
			return true;
		}
		return tmp.radius != radius || tmp.center != center;
	}

	std::vector<unsigned char> CircleCollider::Serialize() const
	{
		std::vector<unsigned char> v;
		const unsigned char* c = (const unsigned char*)&center.x;
		for (unsigned i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		c = (const unsigned char*)&center.y;
		for (unsigned i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		c = (const unsigned char*)&radius;
		for (unsigned i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		v.push_back(0xff);
		v.push_back(0xff);
		v.push_back(0xff);
		return v;
	}
	serialization::Serializable* CircleCollider::Deserialize(std::vector<unsigned char> v) const
	{
		if (v.size() < TotalByteSize())
		{
			throw std::runtime_error("Insufficient amount of bytes for deserialization. ");
		}
		CircleCollider* cC = new CircleCollider();
		if (BIG_ENDIAN)
		{
			unsigned char* c = (unsigned char*)&cC->center.x;
			auto iter = v.begin();
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->center.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->radius;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
		}
		else
		{
			unsigned char* c = (unsigned char*)&cC->center.x;
			auto iter = v.begin();
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->center.y;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
			c = (unsigned char*)&cC->radius;
			for (unsigned i = 0; i < sizeof(double); i++)
			{
				c[i] = *iter;
				iter++;
			}
		}
		return cC;
	}
	const unsigned long CircleCollider::TotalByteSize() const noexcept
	{
		return sizeof(double) * 3 + 3;
	}
}