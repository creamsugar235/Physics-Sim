#include "physics/main.hpp"
#include <iostream>
int main(int argc, char** args)
{
	physics::Run();
	physics::Object o("bruhuh", sf::Sprite(), 0, 0, true);
	o.AddPoint(geometry::Point(10, 0));
	physics::Object o2("bruhuh", sf::Sprite(), 200, 0, true);
	o.AddPoint(geometry::Point(10, 0));
	std::cout<<o.IsOverlapping(o);
	return 0;
}