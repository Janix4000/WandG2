#pragma once

#include <SFML\Graphics\Sprite.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../ResourceManager/ResourceHolder.h"


#include "../World/Floor.h"
#include "../Utility/Vec3.h"

class Entity
{

private:
	sf::Vector2f pos;
	sf::Vector2f size;

	sf::Sprite sprite;
	TexturePtr texture;

	float yFactor = 1.f;
	float paralaxFactor = 300.f;

	float speed = 250.f;

	const sf::RectangleShape& floor;

public:

	Entity(const Floor& floor)
		:
		floor(floor.getShape())
	{
		texture = ResourceHolder::get().textures.acquire("entity");
		sprite.setTexture(*texture);

		size = { float(texture->getSize().x), float(texture->getSize().y) };

		sprite.setOrigin(size.x / 2, size.y);

		setPos({ floor.getPosition().x , floor.getPosition().y });
	}

	void update(float dt)
	{

		sf::Vector2f movement = {0.f, 0.f};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			movement += { 0.f, -speed };
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			movement += { 0.f, speed };
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			movement += { -speed, 0.f };
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			movement += { speed, 0.f };
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			speed += 0.5f;
			std::cout << speed << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			speed -= 0.5f;
			std::cout << speed << std::endl;
		}

		
		movement *= dt;

		move(movement);

		handleBounds();

	}

	void handleInput(const sf::RenderWindow& window)
	{
		
	}

	void render(sf::RenderTarget& renderer) const
	{
		renderer.draw(sprite);
	}

	void setPos(sf::Vector2f position)
	{
		pos = position;
		handleParalax();
		calcSpritePos();
	}

	void move(sf::Vector2f shift)
	{
		setPos(pos + shift);
	}

	sf::Sprite& getSprite()
	{
		return sprite;
	}

	const sf::Vector2f& getPosition() const
	{
		return pos;
	}

private:

	void handleParalax()
	{ 
		yFactor = (paralaxFactor / (floor.getPosition().y - pos.y + paralaxFactor));

		//system("cls");
		//std::cout << yFactor << std::endl;

		sprite.setScale(yFactor, yFactor);
	}

	/*
	void moveSprite(const sf::Vector2f& shift)
	{
		const auto oldSpritePos = sprite.getPosition();
		sprite.setPosition(oldSpritePos + (yFactor * shift));
	}
	*/

	void calcSpritePos()
	{
		const float yShift = (pos.y - floor.getPosition().y) * yFactor;

		sprite.setPosition({ pos.x ,floor.getPosition().y + yShift });
	}

	void initStartingPosition(const sf::Vector2f& position)
	{
		pos = position;

		const auto distToBound = floor.getPosition().y - pos.y;
		sprite.setPosition(pos.x, floor.getPosition().y);
		calcSpritePos();

	}

	void handleBounds()
	{
		const auto shapeSize = floor.getSize();
		const auto shapePos = floor.getPosition();

		const auto sR = shapePos.x + shapeSize.x / 2;
		const auto sL = shapePos.x - shapeSize.x / 2;
		const auto sT = shapePos.y - shapeSize.y;
		const auto sB = shapePos.y;

		const auto R = pos.x + size.x / 2;
		const auto L = pos.x - size.x / 2;
		const auto T = pos.y - size.y;
		const auto B = pos.y;

		sf::Vector2f shift;

		if (R >= sR)
		{
			shift.x += sR - R;
		}
		if (L <= sL)
		{
			shift.x += sL - L;
		}
		if (B >= sB)
		{
			shift.y += sB - B;
		}
		if (T <= sT)
		{
			shift.y += sT - T;
		}

		move(shift);

		//std::cout << pos.x << pos.y << std::endl;
	}
};