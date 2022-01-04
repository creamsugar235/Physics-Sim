#include "../include/geometry/main.hpp"
#include <memory>

namespace geometry
{
	Point::Point()
	{
		this->x = 0;
		this->y = 0;
	}

	Point::Point(const Vector& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	Point::Point(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
	}

	Point::Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	Point::~Point()
	{
	}

	Point Point::Clone() const
	{
		return Point(this->x, this->y);
	}

	Point::operator Vector(void) const
	{
		return Vector(x, y);
	}

	Point Point::operator*(const Point& p)
	{
		return Point(this->x * p.x, this->y * p.y);
	}

	Point Point::operator+(const Point& p)
	{
		return Point(this->x + p.x, this->y + p.y);
	}

	Point Point::operator-(const Point& p)
	{
		return Point(this->x - p.x, this->y - p.y);
	}

	void Point::operator*=(const Point& p)
	{
		this->x *= p.x;
		this->y *= p.y;
	}

	void Point::operator+=(const Point& p)
	{
		this->x += p.x;
		this->y += p.y;
	}

	void Point::operator-=(const Point& p)
	{
		this->x -= p.x;
		this->y -= p.y;
	}

	bool Point::operator^(Line l) const
	{
		return (Line(l.a(), *this).angle() == Line(*this, l.b()).angle());
	}

	bool Point::operator==(const Point& p) const
	{
		return (this-> x == p.x && this->y == p.y);
	}

	bool Point::operator!=(const Point& p) const
	{
		return !(this-> x == p.x && this->y == p.y);
	}

	bool Point::operator>(const Point& p) const
	{
		return Calc::Distance(Origin, p) > Calc::Distance(Origin, *this);
	}

	bool Point::operator<(const Point& p) const
	{
		return Calc::Distance(Origin, p) < Calc::Distance(Origin, *this);
	}

	Point Point::operator()() const
	{
		return Point(x, y);
	}

	void Point::Move(double offsetX, double offsetY)
	{
		this->x += offsetX;
		this->y += offsetY;
	}
	
	int Point::Quadrant(const Point& p) const
	{
		if (p.x < this->x)
		{
			if (p.y < this->y)
			{
				return 3;
			}
			else if (p.y > this->y)
			{
				return 2;
			}
			return 3;
		}
		else if (p.x > this->x)
		{
			if (p.y < this->y)
			{
				return 4;
			}
			else if (p.y > this->y)
			{
				return 1;
			}
			return 1;
		}
		return 0;
	}

	void Point::Rotate(const Point &p, double angle)
	{
		double currentAngle = Calc::GetAngle(p, *this);
		angle += currentAngle;
		if (angle < 0) {angle += (M_PI * 2);}
		if (angle > (M_PI) * 2) {angle -= M_PI;}
		double distance = Calc::Distance(*this, p);
		Point p2 = Calc::GetPointOnCircle(p, distance, angle);
		this->x = p2.x;
		this->y = p2.y;
	}

	std::string Point::ToString() const
	{
		std::string strX = std::to_string(this->x);
		std::string strY = std::to_string(this->y);
		return "(" + strX + ", " + strY + ")";
	}

	std::tuple<double, double> Point::ToTuple() const
	{
		std::tuple<double, double> t(this->x, this->y);
		return t;
	}
}