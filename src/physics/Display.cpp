#include "../include/physics/Display.hpp"
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

	std::ostream& operator<<(std::ostream& os, const Object& o)
	{
		std::string s = "";
		std::string space;
		space = " ";
		for (geometry::Point p: o.ReturnPoints())
		{
			std::cout<<"P: "<<p.ToString()<<std::endl;
			std::cout<<"WHAT"<<p.x<<" "<<p.y<<std::endl;
			s = std::string(s + space + p.ToString());
		}
		return os << s;
	}

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
			Display();
			for (auto& o: world.objects)
			{
				std::cout<<o<<"\n";
			}
			std::cout.flush();
		}
	}

	void Display()
	{
		mainWindow.clear();
		std::function<void(Object* o)> recursiveDisplay = [&](Object* o)
		{
			if (IsInView(o))
			{
				sf::Sprite s = sf::Sprite(*o->texture);
				s.setPosition(sf::Vector2f(o->GetPos().x, o->GetPos().y));
				s.setScale(sf::Vector2f(o->GetScale().x, o->GetScale().y));
				s.rotate(geometry::Calc::Degrees(o->GetTransform().rotation));
				mainWindow.draw(s);
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
		for (auto& iter: textures)
		{
			if (!iter.second.loadFromFile(iter.first))
			{
				exit(1);
			}
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
		for (int i = 0; i < 40; i++)
		{
			int scale = rand() % 100;
			std::vector<geometry::Point> p;
			p.push_back(geometry::Point(scale, 0));
			world.AddObject(Object("circlee", &textures["circlee"], rand() % 50, rand() % 50, p, true));
			world.objects[world.objects.size() - 1]->SetScale(geometry::Point(scale, scale));
		}
	}

	void CheckCollision(){}

	void Time::Tick()
	{
		std::chrono::time_point<clock> t = clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(t - time).count();
		time = clock::now();
	}
}