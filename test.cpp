#include <iostream>
#include <fstream>
#include <string>

class Base
{
public:
	int r = 0;
};

class Derived : public Base
{
public:
	const char * c = "brahugpeafds";
	int d = 3;
};

int main(int argc, char** args)
{
	if (argc - 1)
	{
		std::ofstream file(std::string(args[1]), std::ios::binary);
		Base b;
		Derived d;
		file.write((char*)&d, sizeof(d));
		file.close();
		std::ifstream file2;
		file2.open(args[1], std::ios::in);
		file2.seekg(0);
		file2.read((char*)&b, sizeof(b));
		file2.close();
		std::cout<<d.d<<d.c;
	}
	return 0;
}