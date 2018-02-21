#pragma once

#include "Entity.h"

class TestHero
	:
	public Entity
{
public:
	TestHero()
		:
		Entity()
	{
		setTexture(ResourceHolder::get().textures.acquire("test_hero"));

		speed = 200.f;
	}

	~TestHero() override = default;

	virtual void update(float dt) override
	{
		handleMovement(dt);
	}
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) override
	{}
	virtual void handleInput(const sf::RenderWindow& window) override
	{}
	virtual void render(sf::RenderTarget& renderer) const override
	{
		renderer.draw(sprite);
	}
	virtual sf::Transformable& getObject() override
	{
		return sprite;
	}
	virtual sf::Vector2f getSize() const override
	{
		const auto size = texture->getSize();
		return { float(size.x), float(size.y) };
	}

	void setTexture(TexturePtr newTexture)
	{
		texture = newTexture;
		sprite.setTexture(*texture);

		sf::Vector2f size = { float(texture->getSize().x), float(texture->getSize().y) };
		sprite.setOrigin(size.x / 2.f, size.y);
	}

private:
	TexturePtr texture;
	sf::Sprite sprite;

	float speed = 20.f;

	void handleMovement(float dt)
	{
		sf::Vector2f finalMove = {0.f, 0.f};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			finalMove.y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			finalMove.y += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			finalMove.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			finalMove.x += speed;
		}

		/*
		if (finalMove.x * finalMove.x + finalMove.y * finalMove.y > 0.f)
		{
			std::cout << "Debug move: x: " << finalMove.x << " y: " << finalMove.y << std::endl;
			std::cout << "Debug pos: x: " << getPosition().x << " y: " << getPosition().y << std::endl;

		}
		*/

		move(finalMove * dt);
	}

	
	
};


inline EntityPtr makeTestHero()
{
	return std::make_unique<TestHero>();
}
