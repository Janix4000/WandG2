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

	float speed = 250.f;

public:

	Entity()
	{
		texture = ResourceHolder::get().textures.acquire("entity");
		sprite.setTexture(*texture);

		size = { float(texture->getSize().x), float(texture->getSize().y) };

		sprite.setOrigin(size.x / 2, size.y);

		setPos({500.f, 500.f });
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
		sprite.setPosition(pos);
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

	const sf::Vector2f& getSize() const
	{
		return size;
	}

private:
};