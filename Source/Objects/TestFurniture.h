#pragma once

#include "Entity.h"
#include "../Utility/Random.h"

class TestFurniture
	:
	public Entity
{
public:
	TestFurniture()
	{
		Random<> rng;
		setTexture(ResourceHolder::get().textures.acquire("test_furniture"));
		setPosition({ rng.getFloatInRange(-200.f, 200.f), rng.getFloatInRange(-200.f, 0.f) });
	}

	virtual void update(float dt) override
	{}
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) override
	{}
	virtual void handleInput(const sf::RenderWindow& window) override
	{}
	virtual void render(sf::RenderTarget& renderer) const override
	{
		renderer.draw(shelf);
	}

	virtual sf::Transformable& getObject() override
	{
		return shelf;
	}
	virtual sf::Vector2f getSize() const override
	{
		return sf::Vector2f(texture->getSize());
	}

	void setTexture(TexturePtr newTexture)
	{
		texture = newTexture;
		shelf.setTexture(*texture);

		sf::Vector2f size = { float(texture->getSize().x), float(texture->getSize().y) };
		shelf.setOrigin(size.x / 2.f, size.y);
	}

private:
	sf::Sprite shelf;
	TexturePtr texture;
};