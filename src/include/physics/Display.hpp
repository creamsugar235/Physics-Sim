#pragma once
#include "Object.hpp"
#include "Entity.hpp"
#include "../SFML/Window.hpp"
#include "../SFML/Graphics.hpp"

namespace physics
{
	class Display
	{
		private:
			sf::RenderWindow _window;
			unsigned int _width;
			unsigned int _height;
			std::string _title;
		public:
			Display(unsigned int width, unsigned int height, std::string& title);
			void Close();
			void Draw(const Entity& e);
			void Draw(const sf::Drawable& d);
			unsigned int GetHeight() const noexcept;
			std::string GetTitle() const noexcept;
			unsigned int GetWidth() const noexcept;
			sf::RenderWindow* GetWindow() noexcept;
			const sf::RenderWindow& GetWindow() const noexcept;
			void SetHeight(unsigned int h);
			void SetTitle(std::string windowName);
			void SetWidth(unsigned int w);
			void SetView(sf::View& view);
			void Update(const bool& shouldClear=true);
	};
}