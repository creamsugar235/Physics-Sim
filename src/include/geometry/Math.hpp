#pragma once
#include <tuple>
#include <exception>
namespace geometry
{
	enum ShapeType
	{
		RigidBody,
		StaticBody,
		KinematicBody
	};
	
	class Exception : public std::runtime_error
	{
		std::string what_message;
		public:
			Exception(std::string message) : std::runtime_error(message)
			{
			}
			const char * what()
			{
				return this->what_message.c_str();
			}
	};

	class Point3D
	{
		public:
			double x = 0;
			double y = 0;
			double z = 0;
			Point3D();
			Point3D(const Point3D& p);
			Point3D(double x, double y, double z);
			void Move(double offsetX, double offsetY, double offsetZ);
	};

	struct Quaternion
	{
		public:
			double x;
			double y;
			double z;
			double w;
			Quaternion();
			Quaternion(const Point3D& axis, double angle);
			Quaternion(double x, double y, double z, double w);
			Quaternion operator*(const Quaternion& other) const noexcept;
			std::tuple<std::tuple<double, double, double>> ToRotationMatrix() const;
			bool operator==(const Quaternion& other) const noexcept;
			bool operator!=(const Quaternion& other) const noexcept;
	};
#define DefaultQuaternion Quaternion()
}