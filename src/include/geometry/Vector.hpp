#pragma once
#include <cmath>
#include <vector>
#include <tuple>

namespace geometry
{
	class Line;
	class Vector
	{
		public:
			double x;
			double y;
			Vector();
			Vector(double x, double y);
			double magnitude() const;
			void Normalize();
			Vector Normalized() const;
			double Cross(const Vector& v) const noexcept;
			static Vector Cross(const Vector& v, const double& s);
			static Vector Cross(const double& s, const Vector& v);
			double Dot(const Vector& v) const;
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
			bool operator^(Line l) const;
			bool operator<(const Vector& v) const noexcept;
			bool operator>(const Vector& v) const noexcept;
			Vector operator()() const;
			void Move(double offsetX, double offsetY) noexcept;
			int Quadrant(const Vector& p) const noexcept;
			void Rotate(const Vector& p, double angle) noexcept;
			std::string ToString() const noexcept;
			std::tuple<double, double> ToTuple() const noexcept;
	};
	Vector operator*(const double& d, const Vector& v) noexcept;
	Vector operator+(const double& d, const Vector& v) noexcept;
#define Origin Vector(0, 0)
#define Infinity Vector(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())
}