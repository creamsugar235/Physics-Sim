#pragma once
#include <algorithm>
#include <cmath>
#include <exception>
#include <string>
#include <tuple>
#include <vector>
namespace geometry
{
	class Calc;
	class Line;
	class Exception;
	class Point;
	class Shape;
	class Vector;
	struct Transform;

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
			Point(const Point& p);
			Point(double x, double y);
			~Point();
			Point Clone() const;
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
			Point start;
			Point direction;
			Vector();
			Vector(Point start, Point direction);
	};

	struct Transform
	{
		public:
			Point coords;
			double rotation;
			Vector vector;
	};

	class Shape
	{
		protected:
			std::vector<Point> _points;
			std::vector<Line> _lines;
			std::vector<Vector> _vectors;
			Transform _t;
			Point max;
			bool _isCircle;
		public:
			Shape();
			Shape(const Shape& s);
			Shape(double x, double y, bool isCircle=false);
			Shape(double x, double y, std::vector<Point> points, bool isCircle=false);
			~Shape();
			int shapeType = 0;
			Shape Clone();
			void AddPoint(const Point& p);
			bool IsCircle() const;
			bool IsIn(const Point& p) const;
			bool IsOverlapping(const Shape& s);
			Point GetPos() const;
			double GetRadius() const;
			Transform GetTransform() const;
			void SetPos(double x, double y);
			void SetTransform(const Transform& t);
			void Move(double offsetX, double offsetY);
			std::vector<Point> ReturnPoints() const;
			void Rotate(const Point& p, double angle);
			void Scale(double xFactor, double yFactor);
			std::string ToString() const;

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
	};

	const Point Origin = Point(0, 0);
	const Point Infinity = Point(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
}