#include <iostream>
#include <fstream>
#include <string>
#include <vector>
typedef double f64;
struct Square
{
	f64 x = 0;
	f64 y = 0;
	f64 width = 0;
	f64 height = 0;
};

bool SquareOverLaps(const Square& a, const Square& b)
{
	auto numInRange = [&] (double value, double minVal, double maxVal){
		return (value >= minVal) && (value <= maxVal);
	};
	bool xOverlaps = numInRange(a.x, b.x, b.x + b.width) ||
		numInRange(b.x, a.x, a.x + a.width);
	bool yOverlaps = numInRange(a.y, b.y, b.y + b.height) ||
		numInRange(b.y, a.y, a.y + a.height);
	return xOverlaps && yOverlaps;
}
int main(int argc, char** args)
{
	Square s;
	Square s2;
	s.x = 50;
	s.y = 50;
	s.width = 10;
	s.height = 10;
	s2.x = 60.1;
	s2.y = 60;
	s2.width = 10;
	s2.height = 10;
	std::cout<<std::boolalpha<<SquareOverLaps(s, s2)<<"\n";
	return 0;
}