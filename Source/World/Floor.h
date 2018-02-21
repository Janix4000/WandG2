#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Objects/Entity.h"

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


	void handleBounding(Entity& entity)
	{
		const auto floorSize = getSize();

		const auto pos = entity.getPosition();
		const auto size = entity.getSize();

		const auto fR = 0.f + floorSize.x / 2;
		const auto fL = 0.f - floorSize.x / 2;
		const auto fT = 0.f - floorSize.y;
		const auto fB = 0.f;

		const auto R = pos.x + size.x / 2;
		const auto L = pos.x - size.x / 2;
		const auto T = pos.y;
		const auto B = pos.y;

		sf::Vector2f shift;

		if (R >= fR)
		{
			shift.x += fR - R;
		}
		if (L <= fL)
		{
			shift.x += fL - L;
		}
		if (B >= fB)
		{
			shift.y += fB - B;
		}
		if (T <= fT)
		{
			shift.y += fT - T;
		}

		entity.move(shift);
	}

private:
	sf::RectangleShape floor;
};