#include "../include/geometry/main.hpp"

namespace geometry
{
	Vector::Vector()
	{
	}

	Vector::Vector(double x, double y, double magnitude)
	{
		this->x = x;
		this->y = y;
		this->angle = Calc::GetAngle(Origin, Point(x, y));
		this->magnitude = magnitude;
	}
	
	Vector::Vector(Point p, double magnitude)
	{
		this->x = p.x;
		this->y = p.y;
		this->angle = Calc::GetAngle(Origin, Point(x, y));
		this->magnitude = magnitude;
	}

	Vector Vector::operator-() const noexcept
	{
		return Vector(-x, -y, magnitude);
	}

	Vector Vector::operator+() const noexcept
	{
		return Vector(+x, +y, magnitude);
	}

	bool Vector::operator==(const Vector &v) const noexcept
	{
		return (Point(x, y) == Point(v.x, v.y) && magnitude == v.magnitude && (angle - 0.001 < v.angle && v.angle < angle + 0.001));
	}

	bool Vector::operator!=(const Vector &v) const noexcept
	{
		return !(Point(x, y) == Point(v.x, v.y) && magnitude == v.magnitude && (angle - 0.001 < v.angle && v.angle < angle + 0.001));
	}

	Vector Vector::operator+(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x += v.x;
		result.y += v.y;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude += v.magnitude;
		return result;
	}

	Vector Vector::operator+(const double& d) const noexcept
	{
		Vector result(*this);
		result.x += d;
		result.y += d;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude += d;
		return result;
	}

	void Vector::operator+=(const Vector& v) noexcept
	{
		x += v.x;
		y += v.y;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude += v.magnitude;
	}

	void Vector::operator+=(const double& d) noexcept
	{
		x += d;
		y += d;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude += d;
	}

	Vector Vector::operator-(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x -= v.x;
		result.y -= v.y;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude -= v.magnitude;
		return result;
	}

	Vector Vector::operator-(const double& d) const noexcept
	{
		Vector result(*this);
		result.x -= d;
		result.y -= d;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude -= d;
		return result;
	}

	void Vector::operator-=(const Vector& v) noexcept
	{
		x -= v.x;
		y -= v.y;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude -= v.magnitude;
	}

	void Vector::operator-=(const double& d) noexcept
	{
		x -= d;
		y -= d;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude -= d;
	}

	Vector Vector::operator*(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x *= v.x;
		result.y *= v.y;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude *= v.magnitude;
		return result;
	}

	Vector Vector::operator*(const double& d) const noexcept
	{
		Vector result(*this);
		result.x *= d;
		result.y *= d;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude *= d;
		return result;
	}

	void Vector::operator*=(const Vector& v) noexcept
	{
		x *= v.x;
		y *= v.y;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude *= v.magnitude;
	}

	void Vector::operator*=(const double& d) noexcept
	{
		x *= d;
		y *= d;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude *= d;
	}

	Vector Vector::operator/(const Vector& v) const noexcept
	{
		Vector result(*this);
		result.x /= v.x;
		result.y /= v.y;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude /= v.magnitude;
		return result;
	}

	Vector Vector::operator/(const double& d) const noexcept
	{
		Vector result(*this);
		result.x /= d;
		result.y /= d;
		result.angle = Calc::GetAngle(Origin, Point(result.x, result.y));
		result.magnitude /= d;
		return result;
	}

	void Vector::operator/=(const Vector& v) noexcept
	{
		x /= v.x;
		y /= v.y;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude /= v.magnitude;
	}

	void Vector::operator/=(const double& d) noexcept
	{
		x /= d;
		y /= d;
		angle = Calc::GetAngle(Origin, Point(x, y));
		magnitude /= d;
	}
}