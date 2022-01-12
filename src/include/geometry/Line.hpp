#pragma once
#include <tuple>
#include "Vector.hpp"

namespace geometry
{
	class Line
	{
		private:
			double _length = 0;
			double _angle = 0;
		public:
			Line();
			Line(const Vector& a, const Vector& b);
			Line(const Line& l);
			~Line();
			Vector a;
			Vector b;
			bool operator==(const Line& l) const;
			bool operator!=(const Line& l) const;
			double angle() const;
			Vector GetVectorAlongLine(double distance, bool startFromA = true) const;
			double length() const;
			void Move(double offsetX, double offsetY);
			std::string ToString() const;
			std::tuple<std::tuple<double, double>, std::tuple<double, double>> ToTuple() const;
			void Rotate(const Vector& pivot, double angle);
			void Update();
	};
}