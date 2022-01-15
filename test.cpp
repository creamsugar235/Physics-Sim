#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void bruh()
{
}
class Base
{
	public:
		const char * b = "rejapifsdf";
		int r = 0;
		std::vector<int> ints;
		static void bruh() {}
};

struct Derived : public Base
{
	public:
		const char * c = "brahugpeafds";
		int d = 3;
		static void bruh()
		{
			std::cout<<"bruh\n";
		}
};

int main(int argc, char** args)
{
	if (argc - 1)
	{
		//std::ofstream file(std::string(args[1]), std::ios::binary);
		/*Derived b;
		Derived d;
		for (int i = 0; i < 100; i++)
			d.ints.push_back(i);
		d.c = "fadshfd";
		file.write((char*)&d, sizeof(d));
		file.close();
		
		Derived::bruh();
		void(*t)() = Base::bruh;
		const unsigned char * bb = reinterpret_cast<unsigned char*>(&t);
		std::cout<<std::dec<<(int* )bb<<std::endl;;
		std::ifstream file2;
		file2.open(args[1], std::ios::in);
		file2.seekg(0);
		file2.read((char*)&b, sizeof(b));
		file2.close();*/
		double d = 15000;
		std::vector<unsigned char> v;
		const unsigned char* c= (const unsigned char*) &d;
		for (int i = 0; i < sizeof(double); i++)
		{
			v.push_back(c[i]);
		}
		for (unsigned char UC: v)
		{
			std::cout<<std::hex<<(int)UC<<std::endl;
		}
		double d2 = 0;
		char* c2 = (char*)&d2;
		std::cout<<d2<<std::endl;
		int i = 0;
		for (unsigned char UC: v)
		{
			c2[i] = UC;
			i++;
		}
		std::cout<<d2<<std::endl;
		//std::cout<<b.d<<" "<<b.c<<" "<<b.ints.at(0)<<"\n";
	}
	return 0;
}