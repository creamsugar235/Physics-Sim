#include "src/include/geometry/main.hpp"
#include <iostream>
#include <string>
using namespace geometry;

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
	std::string s("((");
	s = s + std::to_string(v.x) + ", " + std::to_string(v.y) + "), ";
	s = s + std::to_string(Calc::Degrees(v.angle)) + "°, " + std::to_string(v.magnitude) + ")";
	return os << s;
}

int main(int argc, char** args)
{
	Vector v(0, 0, 1);
	Vector v2(10, 10, 1);
	Vector v3 = v2 - v;
	std::cout<<v<<"\n"<<v2<<"\n";
	std::cout<<v3<<std::endl;
	return 0;
}