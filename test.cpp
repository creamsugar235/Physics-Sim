#include <iostream>
#include "src/include/geometry/main.hpp"

using namespace geometry;
int main(int argc, char** args)
{
	Shape s(0, 0, true);
	s.AddPoint(Point(10, 0));
	Shape s2(10, 0, true);
	s2.AddPoint(Point(1, 1));
	Shape s3(0, 0);
	s3.AddPoint(Point(0, 0));
	s3.AddPoint(Point(0, 1));
	s3.AddPoint(Point(1, 1));
	s3.AddPoint(Point(1, 0));
	std::cout<<s.IsOverlapping(s2)<<std::endl;
	std::cout<<s2.IsOverlapping(s)<<std::endl;
	std::cout<<s.IsOverlapping(s3)<<std::endl;
	std::cout<<s2.IsOverlapping(s3)<<std::endl;
	return 0;
}