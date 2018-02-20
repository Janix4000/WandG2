#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Floor
{
public:
	Floor(sf::Vector2f size, sf::Vector2f pos)
	{
		setSize(size);
		setPos(pos);

		floor.setFillColor(sf::Color::Blue);
	}

	void setPos(sf::Vector2f pos)
	{
		floor.setPosition(pos);
	}

	void setSize(sf::Vector2f size)
	{
		floor.setSize(size);
		floor.setOrigin(size.x / 2.f, size.y);
	}

	sf::Vector2f getSize() const
	{
		return floor.getSize();
	}
	sf::Vector2f getPosition() const
	{
		return floor.getPosition();
	}

	sf::RectangleShape& getShape()
	{
		return floor;
	}

	void render(sf::RenderTarget& renderer) const
	{
		renderer.draw(floor);
	}

private:
	sf::RectangleShape floor;
};