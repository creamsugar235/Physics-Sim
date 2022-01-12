#pragma once
#include <algorithm>
#include <cmath>
#include "Vector.hpp"
namespace geometry
{
	class Calc
	{
		public:
			static double Degrees(double angle);
			static double Diagonal(double width, double height);
			static double Distance(const Vector& a, const Vector& b);
			static double GetAngle(const Vector& a, const Vector& b, const Vector& c);
			static double GetAngle(double slope);
			static double GetAngle(const Vector& center, const Vector& Vector);
			static Vector GetVectorOnCircle(const Vector& center, double radius, double angle);
			static double GetSlope(const Vector& a, const Vector& b);
			static bool Intersecting(const Line& a, const Line& b, bool isInfLine = false);
			static Vector VectorOfIntersect(const Line& a, const Line& b, bool isInfLine = false);
	};
}