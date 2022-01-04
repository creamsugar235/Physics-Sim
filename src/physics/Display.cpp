#include "../include/physics/Display.hpp"

namespace physics
{
	Display::Display(unsigned int width, unsigned int height, std::string& title)
	{
		_width = width;
		_height = height;
		_title = title;
		_window.create(sf::VideoMode(width, height), title);
	}

	void Display::Close()
	{
		if (_window.isOpen())
			_window.close();
	}

	void Display::Draw(const Entity& e)
	{
		if (_window.isOpen())
			_window.draw(e.GetSprite());
	}

	void Display::Draw(const sf::Drawable& d)
	{
		if (_window.isOpen())
			_window.draw(d);
	}

	unsigned int Display::GetHeight() const noexcept
	{
		return _height;
	}

	std::string Display::GetTitle() const noexcept
	{
		return _title;
	}

	unsigned int Display::GetWidth() const noexcept
	{
		return _width;
	}

	sf::RenderWindow* Display::GetWindow() noexcept
	{
		return &_window;
	}

	const sf::RenderWindow& Display::GetWindow() const noexcept
	{
		return _window;
	}

	void Display::SetHeight(unsigned int h)
	{
		_height = h;
	}

	void Display::SetTitle(std::string windowName)
	{
		_title = windowName;
		_window.setTitle(_title);
	}

	void Display::SetWidth(unsigned int w)
	{
		_width = w;
	}

	void Display::SetView(sf::View& v)
	{
		_window.setView(v);
	}

	void Display::Update(const bool& shouldClear)
	{
		sf::Event e;
		while (_window.pollEvent(e))	
		{
			if (e.type == sf::Event::Closed)
			{
				_window.close();
			}
		}
		_window.display();
		if (shouldClear)
			_window.clear();
	}
}