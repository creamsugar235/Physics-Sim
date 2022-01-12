#include "../include/physics/Algo.hpp"
#include "../include/physics/OstreamOverloads.hpp"
#include <iostream>

namespace algo
{
	CollisionPoints FindCircleCircleCollisionPoints(
		const CircleCollider* a, const Transform& ta,
		const CircleCollider* b, const Transform& tb
	)
	{
		CollisionPoints c;	
		double r = geometry::Calc::Distance(a->center + ta.position, b->center + tb.position);
		// If the sum of their radii is greater than or equal to the distance between their centers
		if (a->radius + b->radius >= r)
		{
			geometry::Line l(a->center, b->center);
			c.a = ta.position + geometry::Vector(l.GetVectorAlongLine(l.length() - a->radius));
			c.b = tb.position + geometry::Vector(l.GetVectorAlongLine(l.length() - b->radius, false));
			c.depth = l.length();
			c.normal = c.b - c.a;
			c.normal.Normalize();
			c.hasCollision = true;
		}
		else
		{
			c.hasCollision = false;
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
				lines.push_back(Line(Vector(ta.position.x + (pt - 1)->x, ta.position.y + (pt - 1)->y),
					Vector(ta.position.x + pt->x, ta.position.y + pt->y)));
			}
			std::vector<Vector> listOfIntersections;
			for (auto&l: lines)
			{
				// find the two Vectors of intersects between a circle and a line
				Vector d((l.b.x - l.a.x) / l.length(), (l.b.y - l.a.y) / l.length());
				double t = d.x * (b->center.x - l.a.x) + d.y * (b->center.y - l.a.y);
				Vector e(t * d.x + l.a.x, t * d.y + l.a.y);
				double dis = Calc::Distance(e, b->center);
				// if intersecting
				if (dis < b->radius)
				{
					double dt = sqrt(pow(b->radius, 2) - pow(dis, 2));
					Vector f((t - dt) * d.x + l.a.x, (t - dt) * d.y + l.a.y);
					Vector g((t + dt) * d.x + l.a.x, (t + dt) * d.y + l.a.y);
					listOfIntersections.push_back(Line(f, g).GetVectorAlongLine(Calc::Distance(f, g) / 2));
				}
			}
			Vector closest;
			bool reached = false;
			for (const Vector& p: listOfIntersections)
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
			c.b = geometry::Vector(closest);
			c.a = geometry::Vector(Line(b->center, closest).GetVectorAlongLine(b->radius));
			c.depth = Calc::Distance(c.a, c.b);
			c.normal = c.b - c.a;
			c.normal.Normalize();
			c.hasCollision = true;
			return c;
		}
		return c;
	}

	geometry::Vector getCentroid(std::vector<geometry::Vector> points)
	{
		if (points.size())
		{
			geometry::Vector first = points.at(0);
			geometry::Vector last = points.at(points.size() - 1);
			if (first.x != last.x || first.y != last.y)
			{
				points.push_back(first);
			}
			double twiceArea = 0, x = 0, y = 0, f = 0;
			geometry::Vector p1, p2;
			// absolutely no clue what this does, it just works lol
			for (size_t i = 0, j = points.size() - 1; i < points.size(); j=i++)
			{
				p1 = points[i]; p2 = points[j];
				f = (p1.y - first.y) * (p2.x - first.x) - (p2.y - first.y) * (p1.x - first.x);
				twiceArea += f;
				x += (p1.x + p2.x - 2 * first.x) * f;
				y += (p1.y + p2.y - 2 * first.y) * f;
			}
			f = twiceArea * 3;
			return geometry::Vector(x / f + first.x, y / f + first.y);
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
		c.hasCollision = false;
		std::vector<geometry::Vector> pointIntersectsB;
		for (const geometry::Vector& p: b->points)
		{
			if (DynamicColliderVectorIsColliding(a, ta, p))
			{
				pointIntersectsB.push_back(p);
			}
		}
		if (!pointIntersectsB.size())
			return c;
		geometry::Vector closest = pointIntersectsB.at(0);
		bool reached = false;
		geometry::Vector centroidB = getCentroid(b->points);
		for (const geometry::Vector& p: pointIntersectsB)
		{
			if (!reached)
			{
				reached = true; closest = p; continue;
			}
			if (geometry::Calc::Distance(p, centroidB) < geometry::Calc::Distance(closest, centroidB))
				closest = p; 
		}
		c.b = tb.position + closest;
		std::vector<geometry::Vector> pointIntersectsA;
		for (const geometry::Vector& p: a->points)
		{
			if (DynamicColliderVectorIsColliding(b, tb, p))
			{
				pointIntersectsA.push_back(p);
			}
		}
		if (!pointIntersectsA.size())
			return c;
		closest = geometry::Origin;
		reached = false;
		geometry::Vector centroidA = getCentroid(a->points);
		for (const geometry::Vector& p: pointIntersectsA)
		{
			if (!reached)
			{
				reached = true; closest = p; continue;
			}
			if (geometry::Calc::Distance(p, centroidA) < geometry::Calc::Distance(closest, centroidA))
			{
				closest = p;
			}
		}
		c.a = ta.position + closest;
		c.depth = geometry::Calc::Distance(c.a, c.b);
		c.normal = (c.b - c.a);
		c.normal.Normalize();
		c.hasCollision = true;
		return c;
	}

	bool DynamicColliderVectorIsColliding(
		const DynamicCollider* a, const Transform& ta,
		const geometry::Vector& b
	)
	{
		if (a->points.size() <3) {return false;}
		geometry::Vector max = *max_element(a->points.begin(), a->points.end());
		max += ta.position;
		geometry::Line line(b, geometry::Vector(max.x + (1 * max.x > b.x ? 1 : -1), b.y));
		std::vector<geometry::Line> trueLines;
		for (auto pt = a->points.begin() + 1;pt != a->points.end(); pt++)
		{
			trueLines.push_back(geometry::Line(ta.position + *(pt - 1), ta.position + *pt));
		}
		trueLines.push_back(geometry::Line(ta.position + a->points.at(a->points.size() - 1), ta.position + a->points.at(0)));
		std::vector<geometry::Vector> listOfIntersections = std::vector<geometry::Vector>();
		for (auto l = trueLines.begin(); l != trueLines.end(); l++)
		{
			if (geometry::Calc::Intersecting(*l, line))
			{
				if (!listOfIntersections.size() || !std::count(listOfIntersections.begin(), listOfIntersections.end(), (geometry::Calc::VectorOfIntersect(*l, line))))
				{
					listOfIntersections.push_back(geometry::Calc::VectorOfIntersect(*l, line));
				}
			}
		}
		return listOfIntersections.size() % 2;
	}
}