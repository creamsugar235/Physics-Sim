#include "../include/geometry/main.hpp"

namespace geometry
{

	Shape::Shape()
	{
		this->_points = std::vector<Point>(0);
	}

	Shape::Shape(const Shape& s)
	{
		this->_points = s.ReturnPoints();
		this->_isCircle = s.IsCircle();
		this->_t = s.GetTransform();
		if (!_isCircle)
		{
			for (auto& p: _points)
			{
				p += this->_t.coords;
			}
			for (size_t i = 0ULL; i < _points.size(); i++)
			{
				this->_lines.push_back(Line(_points[i], _points[(i + 1) % _points.size()]));
			}
		}
		else
		{
			if (_points.size() >= 1)
			{
				_points.push_back(_points[0]);
			}
		}
	}


	Shape::Shape(double x, double y, bool isCircle)
	{
		this->_points = std::vector<Point>(0);
		this->_t.coords += Point(x, y);
		_isCircle = isCircle;
	}

	Shape::Shape(double x, double y, std::vector<Point> points, bool isCircle)
	{
		_isCircle = isCircle;
		this->_t.coords += Point(x, y);
		this->_points = points;
		if (!isCircle)
		{
			for (auto p = _points.begin(); p != _points.end(); p++)
			{
				*p = *p + this->_t.coords;
			}
			for (size_t i = 0ULL; i < _points.size(); i++)
			{
				this->_lines.push_back(Line(_points[i], _points[(i + 1) % _points.size()]));
			}
		}
		else
		{
			if (points.size() >= 1)
			{
				_points.push_back(points[0]);
			}
		}
	}

	Shape::~Shape()
	{
	}
	
	Shape Shape::Clone()
	{
		return Shape(this->_t.coords.x, this->_t.coords.y, this->_points, _isCircle);
	}

	void Shape::AddPoint(const Point& p)
	{
		if (!_isCircle || (_isCircle && _points.size() == 0))
		{
			_points.push_back(this->_t.coords + p);
			if (_lines.size())
			{
				_lines.push_back(Line(_lines[_lines.size()].b, p));
				_lines[0].a = p;
			}
			else if (_points.size() >= 2)
			{
				_lines.push_back(Line(_points[0], _points[1]));
			}
			if (p > max)
				max = *max_element(this->_points.begin(), this->_points.end());
		}
	}

	bool Shape::IsCircle() const
	{
		return _isCircle;
	}

	bool Shape::IsIn(const Point& p) const //O(n) complexity n = length of lines in object
	{
		if (_points.size())
		{
			if (_isCircle)
				return Calc::Distance(_t.coords, _points[0]) <= Calc::Distance(_t.coords, p);
			Line line = Line(p, Point(max.x + (1 * max.x > p.x ? 1 : -1), p.y));
			std::vector<Point> listOfIntersections = std::vector<Point>();
			for (const auto& l: _lines)
			{
				if (Calc::Intersecting(l, line))
				{
					if (!listOfIntersections.size() || !std::count(listOfIntersections.begin(), listOfIntersections.end(), (Calc::PointOfIntersect(l, line))))
					{
						listOfIntersections.push_back(Calc::PointOfIntersect(l, line));
					}
				}
			}
			return listOfIntersections.size() % 2;
		}
		return false;
	}

	bool Shape::IsOverlapping(const Shape& s)
	{
		for (const auto& p : s.ReturnPoints())
		{
			if (IsIn(p))
				return true;
		}
		return false;
	}

	void Shape::Move(double offsetX, double offsetY)
	{
		this->_t.coords = this->_t.coords + Point(offsetX, offsetY);
		for (auto p = _points.begin(); p != _points.end(); p++)
		{
			p->Move(offsetX, offsetY);
		}
		for (auto l = _lines.begin(); l != _lines.end(); l++)
		{
			l->Move(offsetX, offsetY);
		}
	}

	Point Shape::GetPos() const
	{
		return _t.coords;
	}

	Transform Shape::GetTransform() const
	{
		return _t;
	}

	void Shape::SetPos(double x, double y)
	{
		double xDif = _t.coords.x - x;
		double yDif = _t.coords.y - y;
		Move(xDif, yDif);
	}

	void Shape::SetTransform(const Transform& t)
	{
		_t = t;
	}

	std::vector<Point> Shape::ReturnPoints() const
	{
		return _points;
	}

	void Shape::Rotate(const Point& p, double angle)
	{
		for (auto& p: _points)
		{
			p.Rotate(p, angle);
		}
		for (auto& l: _lines)
		{
			l.Rotate(p, angle);
		}
	}

	void Shape::Scale(double xFactor, double yFactor)
	{
		for (auto& p: _points)
		{
			p.x *= xFactor;
			p.y *= yFactor;
		}
		for (auto& l: _lines)
		{
			l = Line(Point(l.a().x * xFactor, l.a().y * yFactor), Point(l.b().x * xFactor, l.b().y * yFactor));
		}
	}

	std::string Shape::ToString() const
	{
		return "Shape";
	}
}