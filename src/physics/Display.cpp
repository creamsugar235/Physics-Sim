#include "../include/physics/Display.hpp"
#include "../include/physics/StopWatch.hpp"
#include <functional>
#include <iostream>
#include <random>

namespace physics
{
	const std::string name = "PHYSICS";
	sf::RenderWindow mainWindow;
	std::map<std::string, sf::Texture> textures;
	World world;
	const std::map<std::string, std::string> texturePaths = {
		{"circle", "bin/textures/circle.png"},
		{"circle_hit", "bin/textures/circle_orange.png"}
	};
	sf::View camera;

	void Update()
	{
		world.Update();
	}

	void Run()
	{
		Load();
		Start();
		mainWindow.create(sf::VideoMode(500, 500), name);
		camera = mainWindow.getDefaultView();
		camera.setSize(500, -500);
		mainWindow.setView(camera);
		while (mainWindow.isOpen())
		{
			Time::Tick();
			sf::Event e;
			while (mainWindow.pollEvent(e))
			{
				if (e.type == sf::Event::Closed)
				{
					mainWindow.close();
				}
			}
			Update();
			StopWatch sw;
			sw.Start();
			CheckCollision();
			sw.Stop();
			std::cout<<"Duration: "<<sw.Duration()<<std::endl;
			sw.Reset();
			Display();
			//std::cout<<Time::deltaTime<<std::endl;
		}
	}

	void Display()
	{
		mainWindow.clear();
		std::function<void(Object* o)> recursiveDisplay = [&](Object* o)
		{
			if (IsInView(o))
			{
				mainWindow.draw(o->sprite);
			}
			if (o->children.size())
			{
				for (auto& child: o->children)
				{
					recursiveDisplay(child);
				}
			}
		};
		for (auto& o: world.objects)
		{
			recursiveDisplay(o);
		}
		mainWindow.display();
	}

	void Load()
	{
		for (auto& iter: texturePaths)
		{
			textures[iter.first] = sf::Texture();
			if (!textures[iter.first].loadFromFile(iter.second))
				exit(1);
		}
	}

	bool IsInView(Object* o)
	{
		Object camBox;
		sf::FloatRect c = camera.getViewport();
		camBox.AddPoint(geometry::Point((double)c.left, (double)c.top));
		camBox.AddPoint(geometry::Point((double)c.left +(double)c.width, c.top));
		camBox.AddPoint(geometry::Point((double)c.left + c.width, (double)c.top + c.height));
		camBox.AddPoint(geometry::Point((double)c.left, (double)c.top + c.height));
		return camBox.IsOverlapping(*o);
	}

	void Start()
	{
		srand(time(NULL));
		for (int i = 0; i < 10; i++)
		{
			int scale = fmod(rand(), 2);
			std::vector<geometry::Point> p;
			p.push_back(geometry::Point(scale, 0));
			world.AddObject(Object("circlee", sf::Sprite(textures["circle"]), rand() % 500, rand() % 500, p, true));
			world.objects[world.objects.size() - 1]->SetScale(geometry::Point(scale, scale));
		}
	}

	template <typename T>
	bool In(std::vector<T> v, const T& val)
	{
		for (const auto& p: v)
		{
			if (p == val)
				return true;
		}
		return false;
	}

	void CheckCollision()
	{
		for (auto& obj : world.objects)
		{
			for (auto& other: world.objects)
			{
				if (*obj != *other)
				{
					if (obj->IsOverlapping(*other))
					{
						if (In(obj->GetCollidedEntities(), other))
						{
							obj->OnCollisionStay(other);
						}
						else if (!In(obj->GetCollidedEntities(), other))
						{
							obj->OnCollisionEnter(other);
						}
					}
					if (In(obj->GetCollidedEntities(), other) && !obj->IsOverlapping(*other))
					{
						obj->OnCollisionExit(other);
					}					
				}
			}
		}
	}

	void Time::Tick()
	{
		std::chrono::time_point<clock> t = clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - time).count();
		time = clock::now();
	}
}