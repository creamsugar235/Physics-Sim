#include "../include/geometry/Calc.hpp"
#include "../include/geometry/Line.hpp"

namespace geometry
{
	Line::Line()
	{
	}

	Line::Line(const Vector& a, const Vector& b)
	{
		this->a = a;
		this->b = b;
		this->_length = Calc::Distance(this->a, this->b);
		this->_angle = Calc::GetAngle(this->a, this->b);
	}

	Line::Line(const Line& l)
	{
		this->a = l.a();
		this->b = l.b();
		this->_length = Calc::Distance(this->a, this->b);
		this->_angle = Calc::GetAngle(this->a, this->b);
	}

	Line::~Line()
	{
	}

	bool Line::operator==(const Line& l) const
	{
		return (this->a == l.a() && this->b == l.b());
	}

	bool Line::operator!=(const Line& l) const
	{
		return !(this->a == l.a() && this->b == l.b());
	}

	double Line::angle() const
	{
		return _angle;
	}

	Vector Line::GetVectorAlongLine(double distance, bool startFromA) const
	{
		Vector begin = startFromA ? this->a : this->b;
		return Calc::GetVectorOnCircle(begin, distance, this->_angle);
	}

	double Line::length() const
	{
		return this->_length;
	}

	void Line::Move(double offsetX, double offsetY)
	{
		this->a.Move(offsetX, offsetY);
		this->b.Move(offsetX, offsetY);
	}

	std::string Line::ToString() const
	{
		return "(" + this->a.ToString() + ", " + this->b.ToString() + ")";
	}

	std::tuple<std::tuple<double, double>, std::tuple<double, double>> Line::ToTuple() const
	{
		return std::tuple<std::tuple<double, double>, std::tuple<double, double>>(this->a.ToTuple(), this->b.ToTuple());
	}

	void Line::Rotate(const Vector& pivot, double angle)
	{
		this->a.Rotate(pivot, angle);
		this->b.Rotate(pivot, angle);
		Update();
	}
	void Line::Update()
	{
		this->_length = Calc::Distance(this->a, this->b);
		this->_angle = Calc::GetAngle(this->a, this->b);
	}
}