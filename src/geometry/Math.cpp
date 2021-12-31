#include "../include/geometry/main.hpp"

namespace geometry
{
	Point3D::Point3D()
	{
	}

	Point3D::Point3D(const Point3D& p)
	{
		x = p.x;
		y =  p.y;
		z = p.z;
	}

	Point3D::Point3D(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point3D::Move(double offsetX, double offsetY, double offsetZ)
	{
		x += offsetX;
		y += offsetY;
		z += offsetZ;
	}


	Quaternion::Quaternion()
	{
		x = 1;
		y = 0;
		z = 0;
		w = 0;
	}

	Quaternion::Quaternion(const Point3D& axis, double angle)
	{
		w = cos(angle / 2);
		x = axis.x * sin(angle / 2);
		y = axis.y * sin(angle / 2);
		z = axis.z * sin(angle / 2);
	}

	Quaternion::Quaternion(double x, double y, double z, double w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
	{
		Quaternion q;
		q.w = (w * other.w - x * other.x - y * other.y - z * other.z);
		q.x = (w * other.x + x * other.w + y * other.z - z * other.y);
		q.y = (w * other.y - x * other.z + y * other.w + z * other.x);
		q.z = (w * other.z + x * other.y - y * other.x + z * other.w);
		return q;
	}
}