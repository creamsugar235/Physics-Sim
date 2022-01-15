#include "../include/geometry/main.hpp"

namespace geometry
{
	Vector::Vector()
	{
		x = 0;
		y = 0;
	}

	Vector::Vector(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	double Vector::Cross(const Vector& v) const noexcept
	{
		return x * v.y - y * v.x;
	}

	Vector Vector::Cross(const Vector& v, const double& s)
	{
		return Vector(s * v.y, -s * v.x);
	}

	Vector Vector::Cross(const double& s, const Vector& v)
	{
		return Vector(-s * v.y, s * v.x);
	}

	double Vector::Dot(const Vector& v) const
	{
		return x * v.x + y * v.y;
	}

	double Vector::magnitude() const
	{
		return x * x + y * y;
	}

	void Vector::Normalize()
	{
		double mag = magnitude();
		if (mag > 0.00001)
			*this = *this / mag;
		else
			*this = Vector(0, 0);
	}

	Vector Vector::Normalized() const
	{
		Vector v = Vector(this->x, this->y);
		v.Normalize();
		return v;
	}

	Vector operator*(const double& d, const Vector& v) noexcept
	{
		return Vector(d * v.x, d * v.y);
	}

	Vector operator+(const double& d, const Vector& v) noexcept
	{
		return Vector(d + v.x, d + v.y);
	}

	Vector Vector::operator-() const noexcept
	{
		return Vector(-x, -y);
	}

	Vector Vector::operator+() const noexcept
	{
		return Vector(+x, +y);
	}

	bool Vector::operator==(const Vector &v) const noexcept
	{
		return x == v.x && y == v.y;
	}

	bool Vector::operator!=(const Vector &v) const noexcept
	{
		return x != v.x || y != v.y;
	}

	Vector Vector::operator+(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x += v.x;
		result.y += v.y;
		return result;
	}

	Vector Vector::operator+(const double& d) const noexcept
	{
		Vector result(*this);
		result.x += d;
		result.y += d;
		return result;
	}

	void Vector::operator+=(const Vector& v) noexcept
	{
		x += v.x;
		y += v.y;
	}

	void Vector::operator+=(const double& d) noexcept
	{
		x += d;
		y += d;
	}

	Vector Vector::operator-(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x -= v.x;
		result.y -= v.y;
		return result;
	}

	Vector Vector::operator-(const double& d) const noexcept
	{
		Vector result(*this);
		result.x -= d;
		result.y -= d;
		return result;
	}

	void Vector::operator-=(const Vector& v) noexcept
	{
		x -= v.x;
		y -= v.y;
	}

	void Vector::operator-=(const double& d) noexcept
	{
		x -= d;
		y -= d;
	}

	Vector Vector::operator*(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x *= v.x;
		result.y *= v.y;
		return result;
	}

	Vector Vector::operator*(const double& d) const noexcept
	{
		Vector result(*this);
		result.x *= d;
		result.y *= d;
		return result;
	}

	void Vector::operator*=(const Vector& v) noexcept
	{
		x *= v.x;
		y *= v.y;
	}

	void Vector::operator*=(const double& d) noexcept
	{
		x *= d;
		y *= d;
	}

	Vector Vector::operator/(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x /= v.x;
		result.y /= v.y;
		return result;
	}

	Vector Vector::operator/(const double& d) const noexcept
	{
		Vector result(*this);
		result.x /= d;
		result.y /= d;
		return result;
	}

	void Vector::operator/=(const Vector& v) noexcept
	{
		x /= v.x;
		y /= v.y;
	}

	void Vector::operator/=(const double& d) noexcept
	{
		x /= d;
		y /= d;
	}

	bool Vector::operator^(Line l) const
	{
		return (Line(l.a(), *this).angle() == Line(*this, l.b()).angle());
	}

	bool Vector::operator<(const Vector& v) const noexcept
	{
		return Calc::Distance(Origin, v) > Calc::Distance(Origin, *this);
	}

	bool Vector::operator>(const Vector& v) const noexcept
	{
		return Calc::Distance(Origin, v) < Calc::Distance(Origin, *this);
	}

	Vector Vector::operator()() const
	{
		return Vector(x, y);
	}

	void Vector::Move(double offsetX, double offsetY) noexcept
	{
		this->x += offsetX;
		this->y += offsetY;
	}

	int Vector::Quadrant(const Vector& p) const noexcept
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

	void Vector::Rotate(const Vector& p, double angle) noexcept
	{
		double currentAngle = Calc::GetAngle(p, *this);
		angle += currentAngle;
		if (angle < 0) {angle += (M_PI * 2);}
		if (angle > (M_PI) * 2) {angle -= M_PI;}
		double distance = Calc::Distance(*this, p);
		Vector v2 = Calc::GetVectorOnCircle(p, distance, angle);
		this->x = v2.x;
		this->y = v2.y;
	}

	std::string Vector::ToString() const noexcept
	{
		std::string strX = std::to_string(this->x);
		std::string strY = std::to_string(this->y);
		return "(" + strX + ", " + strY + ")";
	}
	
	std::tuple<double, double> Vector::ToTuple() const noexcept
	{
		return std::tuple<double, double>(this->x, this->y);
	}
}