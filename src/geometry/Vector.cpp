#include "../include/geometry/main.hpp"

namespace geometry
{
	Vector::Vector()
	{
	}

	Vector::Vector(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	
	Vector::Vector(Point p)
	{
		this->x = p.x;
		this->y = p.y;
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
		Vector v = *this;
		v.Normalized();
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
}