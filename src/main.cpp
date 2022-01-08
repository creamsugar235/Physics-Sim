#include "include/physics/Scene.hpp"
#include "include/SFML/Graphics.hpp"
#include <iostream>
#include <chrono>
using namespace physics;
using namespace geometry;

class Time final
{
	public:
		typedef std::chrono::steady_clock clock;
		static inline std::chrono::time_point<clock> time = clock::now();
		static inline double deltaTime = -1;
		static void Tick();
};

void Time::Tick()
{
	std::chrono::time_point<clock> t = clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - time).count();
	time = clock::now();
}

int main(int argc, char** args)
{
	std::cout.precision(100);
	sf::RenderTexture rT;
	rT.create(500, 500);
	sf::RectangleShape r;
	//r.setPosition(250, 250);
	r.setFillColor(sf::Color::Red);
	r.setSize(sf::Vector2f(10, 10));
	rT.draw(r);
	sf::Sprite spr(rT.getTexture());
	Scene s(geometry::Vector(0, -0.981), 0);
	Time __t__;
	DynamicCollider d = DynamicCollider(Point(0, 0), Point(0, 0), Point(10, 0), Point(10, 10));
	Transform t;
	t.position = Point(250, 250);
	Rigidbody c(t, d, false, true);
	Entity e("bruh", c, t, spr);
	DynamicCollider d2 = DynamicCollider(Point(0, 0), Point(0, 0), Point(500, 0), Point(500, 20), {Point(0, 20)});
	Transform t2;
	t2.position = Point(0, -4000);
	Rigidbody c2(t2, d2, false, true, 100000);
	Entity floor("floor", c2, t2, spr);
	sf::RenderWindow w;
	s.AddEntity(e);
	s.AddEntity(floor);
	while (s.display->GetWindow()->isOpen())
	{
		Time::Tick();
		s.Step(Time::deltaTime);
		std::cout<<s.GetEntities().at(0)->GetCollisionObject().GetPosition().ToString()<<"\n";
		std::cout<<s.GetEntities().at(1)->GetCollisionObject().GetPosition().ToString()<<"\n";
		s.display->Update();
	}
	return 0;
}