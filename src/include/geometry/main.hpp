#pragma once
#include <algorithm>
#include <cmath>
#include <exception>
#include <string>
#include <tuple>
#include <vector>
#include <map>
namespace geometry
{
	class Calc;
	class Line;
	class Exception;
	class Point;
	class Point3D;
	class Vector;
	struct Quaternion;

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

	class Point
	{
		public:
			double x = 0;
			double y = 0;
			Point();
			Point(const Vector& v);
			Point(const Point& p);
			Point(double x, double y);
			~Point();
			Point Clone() const;
			operator Vector() const;
			Point operator*(const Point& p);
			Point operator+(const Point& p);
			Point operator-(const Point& p);
			void operator+=(const Point& p);
			void operator*=(const Point& p);
			void operator-=(const Point& p);
			bool operator^(Line l) const;
			bool operator==(const Point& p) const;
			bool operator!=(const Point& p) const;
			bool operator<(const Point& p) const;
			bool operator>(const Point& p) const;
			Point operator()() const;
			void Move(double offsetX, double offsetY);
			int Quadrant(const Point& p) const;
			void Rotate(const Point& p, double angle);
			std::string ToString() const;
			std::tuple<double, double> ToTuple() const;
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
	};

	class Line
	{
		private:
			double _length = 0;
			double _angle = 0;
		public:
			Line();
			Line(const Point& a, const Point& b);
			Line(const Line& l);
			~Line();
			Point a;
			Point b;
			bool operator==(const Line& l) const;
			bool operator!=(const Line& l) const;
			double angle() const;
			Point GetPointAlongLine(double distance, bool startFromA = true) const;
			double length() const;
			void Move(double offsetX, double offsetY);
			std::string ToString() const;
			std::tuple<std::tuple<double, double>, std::tuple<double, double>> ToTuple() const;
			void Rotate(const Point& pivot, double angle);
			void Update();
	};

	class Vector
	{
		public:
			double x;
			double y;
			double angle;
			double magnitude;
			Vector();
			Vector(double x, double y, double magnitude);
			Vector(Point p, double magnitude);
			Vector operator-() const noexcept;
			Vector operator+() const noexcept;
			bool operator==(const Vector& v) const noexcept;
			bool operator!=(const Vector& v) const noexcept;
			Vector operator-(const Vector& v) const noexcept;
			Vector operator-(const double& d) const noexcept;
			void operator-=(const Vector& v) noexcept;
			void operator-=(const double& d) noexcept;
			Vector operator+(const Vector& v) const noexcept;
			Vector operator+(const double& d) const noexcept;
			void operator+=(const Vector& v) noexcept;
			void operator+=(const double& d) noexcept;
			Vector operator/(const Vector& v) const noexcept;
			Vector operator/(const double& d) const noexcept;
			void operator/=(const Vector& v) noexcept;
			void operator/=(const double& d) noexcept;
			Vector operator*(const Vector& v) const noexcept;
			Vector operator*(const double& d) const noexcept;
			void operator*=(const Vector& v) noexcept;
			void operator*=(const double& d) noexcept;
	};
	
	class Calc
	{
		public:
			static double Degrees(double angle);
			static double Diagonal(double width, double height);
			static double Distance(const Point& a, const Point& b);
			static double GetAngle(const Point& a, const Point& b, const Point& c);
			static double GetAngle(double slope);
			static double GetAngle(const Point& center, const Point& point);
			static Point GetPointOnCircle(const Point& center, double radius, double angle);
			static double GetSlope(const Point& a, const Point& b);
			static bool Intersecting(const Line& a, const Line& b, bool isInfLine = false);
			static Point PointOfIntersect(const Line& a, const Line& b, bool isInfLine = false);
			static double DotProduct(const Vector& a, const Vector& b);
	};

#define Origin Point(0, 0)
#define Infinity Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())
#define DefaultQuaternion Quaternion()
}