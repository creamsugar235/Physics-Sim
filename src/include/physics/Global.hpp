#pragma once
#include <string>
#include <map>
#include "../SFML/Graphics.hpp"
#include "World.hpp"

namespace physics
{
	class World;
	extern const std::string name;
	extern sf::RenderWindow mainWindow;
	extern std::map<std::string, sf::Texture> textures;
	extern World world;
	extern double speedCap;
}