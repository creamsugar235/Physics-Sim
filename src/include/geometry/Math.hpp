#pragma once
#include <tuple>
#include <exception>
#include <type_traits>
typedef double f64;
typedef float f32;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
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
			f64 x = 0;
			f64 y = 0;
			f64 z = 0;
			Point3D();
			Point3D(const Point3D& p);
			Point3D(f64 x, f64 y, f64 z);
			void Move(f64 offsetX, f64 offsetY, f64 offsetZ);
	};

	struct Quaternion
	{
		public:
			f64 x;
			f64 y;
			f64 z;
			f64 w;
			Quaternion();
			Quaternion(const Point3D& axis, f64 angle);
			Quaternion(f64 x, f64 y, f64 z, f64 w);
			Quaternion operator*(const Quaternion& other) const noexcept;
			std::tuple<std::tuple<f64, f64, f64>> ToRotationMatrix() const;
			bool operator==(const Quaternion& other) const noexcept;
			bool operator!=(const Quaternion& other) const noexcept;
	};
#define DefaultQuaternion Quaternion()
}