#include "../include/physics/Algo.hpp"

namespace algo
{
	CollisionPoints FindCircleCircleCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		double r = pow(a->radius + b->radius, 2);
		if (r < pow(a->center.x + b->center.x, 2) + pow(a->center.y + b->center.y, 2))
		{
			geometry::Line l(a->center, b->center);
			c.a = l.GetPointAlongLine(l.length() - a->radius);
			c.b = l.GetPointAlongLine(l.length() - b->radius, false);
			c.depth = l.length();
			c.normal = geometry::Vector(c.b) - geometry::Vector(c.a);
			c.normal.magnitude = 1;
			c.hasCollision = true;
		}
		return c;
	}

	CollisionPoints FindDynamicCircleCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		if (a->points.size())
		{
			using namespace geometry;
			std::vector<Line> lines;
			for (auto pt = a->points.begin() + 1; pt != a->points.end(); pt++)
			{
				lines.push_back(Line(Point(ta.position.x + (pt - 1)->x, ta.position.y + (pt - 1)->y),
					Point(ta.position.x + pt->x, ta.position.y + pt->y)));
			}
			std::vector<Point> listOfIntersections;
			for (auto&l: lines)
			{
				// find the two points of intersects between a circle and a line
				Point d((l.b.x - l.a.x) / l.length(), (l.b.y - l.a.y) / l.length());
				double t = d.x * (b->center.x - l.a.x) + d.y * (b->center.y - l.a.y);
				Point e(t * d.x + l.a.x, t * d.y + l.a.y);
				double dis = Calc::Distance(e, b->center);
				// if intersecting
				if (dis < b->radius)
				{
					double dt = sqrt(pow(b->radius, 2) - pow(dis, 2));
					Point f((t - dt) * d.x + l.a.x, (t - dt) * d.y + l.a.y);
					Point g((t + dt) * d.x + l.a.x, (t + dt) * d.y + l.a.y);
					listOfIntersections.push_back(Line(f, g).GetPointAlongLine(Calc::Distance(f, g) / 2));
				}
			}
			Point closest;
			bool reached = false;
			for (const Point& p: listOfIntersections)
			{
				if (!reached)
				{
					closest = p;
					reached = true;
				}
				if (Calc::Distance(b->center, p) < Calc::Distance(b->center, closest))
				{
					closest = p;
				}
			}
			if (!reached)
				return c;
			c.b = closest;
			c.a = Line(b->center, closest).GetPointAlongLine(b->radius);
			c.depth = Calc::Distance(c.a, c.b);
			c.normal = Vector(c.b) - Vector(c.a);
			c.normal.magnitude = 1;
			c.hasCollision = true;
			return c;
		}
		return c;
	}

	geometry::Point getCentroid(std::vector<geometry::Point> points)
	{
		if (points.size())
		{
			geometry::Point first = points.at(0);
			geometry::Point last = points.at(points.size() - 1);
			if (first.x != last.x || first.y != last.y)
			{
				points.push_back(first);
			}
			double twiceArea = 0, x = 0, y = 0, f = 0;
			geometry::Point p1, p2;
			int j;
			// absolutely no clue what this does, it just works lol
			for (int i = 0, j = points.size() - 1; i < points.size(); j=i++)
			{
				p1 = points[i]; p2 = points[j];
				f = (p1.y - first.y) * (p2.x - first.x) - (p2.y - first.y) * (p1.x - first.x);
				twiceArea += f;
				x += (p1.x + p2.x - 2 * first.x) * f;
				y += (p1.y + p2.y - 2 * first.y) * f;
			}
			f = twiceArea * 3;
			return geometry::Point(x / f + first.x, y / f + first.y);
		}
		else
			return geometry::Origin;
	}

	CollisionPoints FindDynamicDynamicCollisionPoints(
		const DynamicCollider* a, const Transform& ta,
		const DynamicCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;
		using namespace geometry;
		Point max = *max_element(a->points.begin(), a->points.end());
		std::vector<Point> pointIntersectsB;
		for (const Point& p: b->points)
		{
			Line line = Line(p, Point(max.x + (1 * max.x > p.x ? 1 : -1), p.y));
			std::vector<Line> lines;
			for (auto pt = a->points.begin() + 1;pt != a->points.end(); pt++)
			{
				lines.push_back(Line(Point(ta.position.x + (pt - 1)->x, ta.position.y + (pt- 1)->y), Point(ta.position.x + pt->x, ta.position.y + pt->y)));
			}
			std::vector<Point> listOfIntersections = std::vector<Point>();
			for (const Line& l: lines)
			{
				if (Calc::Intersecting(l, line))
				{
					if (!listOfIntersections.size() || !std::count(listOfIntersections.begin(),
						listOfIntersections.end(), (Calc::PointOfIntersect(l, line))))
					{
						listOfIntersections.push_back(Calc::PointOfIntersect(l, line));
					}
				}
			}
			if (listOfIntersections.size() % 2)
			{
				pointIntersectsB.push_back(p);
			}
		}
		if (!pointIntersectsB.size())
			return c;
		Point closest;
		bool reached = false;
		Point centroidB = getCentroid(b->points);
		for (const Point& p: pointIntersectsB)
		{
			if (!reached)
				reached = true; closest = p; continue;
			if (Calc::Distance(p, centroidB) < Calc::Distance(closest, centroidB))
				closest = p; 
		}
		c.b = closest;
		max = *max_element(b->points.begin(), b->points.end());
		std::vector<Point> pointIntersectsA;
		for (const Point& p: a->points)
		{
			Line line = Line(p, Point(max.x + (1 * max.x > p.x ? 1 : -1), p.y));
			std::vector<Line> lines;
			for (auto pt = b->points.begin() + 1;pt != b->points.end(); pt++)
			{
				lines.push_back(Line(Point(tb.position.x + (pt - 1)->x, tb.position.y + (pt- 1)->y)
					, Point(tb.position.x + pt->x, tb.position.y + pt->y)));
			}
			std::vector<Point> listOfIntersections = std::vector<Point>();
			for (const Line& l: lines)
			{
				if (Calc::Intersecting(l, line))
				{
					if (!listOfIntersections.size() || !std::count(listOfIntersections.begin(),
						listOfIntersections.end(), (Calc::PointOfIntersect(l, line))))
					{
						listOfIntersections.push_back(Calc::PointOfIntersect(l, line));
					}
				}
			}
			if (listOfIntersections.size() % 2)
			{
				pointIntersectsA.push_back(p);
			}
		}
		closest = geometry::Origin;
		reached = false;
		Point centroidA = getCentroid(a->points);
		for (const Point& p: pointIntersectsA)
		{
			if (!reached)
				reached = true; closest = p; continue;
			if (Calc::Distance(p, centroidA) < Calc::Distance(closest, centroidA))
				closest = p; 
		}
		c.a = closest;
		c.depth = Calc::Distance(c.a, c.b);
		c.normal = Vector(c.b) - Vector(c.a);
		c.normal.magnitude = 1;
			c.hasCollision = true;
		return c;
	}
}