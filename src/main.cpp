#include "include/physics/Scene.hpp"
#include "include/SFML/Graphics.hpp"
#include "physics/main.hpp"
#include "test.hpp"
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
	CircleCollider c(Vector(0, 0), 10);
	Scene s0(Vector(0, 0), 0);
	sf::Sprite s;
	Transform t;
	t.rotation.w = 0;
	t.rotation.x = 0;
	t.rotation.y = 0;
	t.rotation.z = 0;
	t.scale = Vector(0, 0);
	/*t.position.x = std::numeric_limits<double>::max() - 1000;
	t.position.y = std::numeric_limits<double>::max() - 1000;
	t.scale.x = std::numeric_limits<double>::max() - 1000;
	t.scale.y = std::numeric_limits<double>::max() - 1000;
	t.rotation.x = std::numeric_limits<double>::max() - 1000;
	t.rotation.y = std::numeric_limits<double>::max() - 1000;
	t.rotation.z = std::numeric_limits<double>::max() - 1000;
	t.rotation.w = std::numeric_limits<double>::max() - 1000;*/
	for (unsigned char& c: t.Serialize())
	{
		std::cout<<std::hex<<(int)c<<" ";
	}
	auto t2 = (Transform*)t.Deserialize(t.Serialize());
	std::cout<<"\n"<<t2->position<<"\n";
	std::cout<<t2->scale<<"\n";
	std::cout<<t2->rotation;
	std::cout<<std::endl;
	Rigidbody r(t, c, false, false);
	Entity e("brhu", r, t, s);
	if (!test::TestCollisionChecking())
	{
		std::cerr<<"failed\n\a";
		exit(1);
	} else if (!test::TestColliders())
	{
		std::cerr<<"failed\n\a";
		exit(1);
	} else if (!test::TestCollisionObject())
	{
		std::cerr<<"failed\n\a";
		exit(1);
	}
	std::cout<<"Success!\n";
	return 0;
}