#pragma once

#include "Object.h"
#include "../Utility/Random.h"

class TestFurniture
	:
	public Object
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
		renderer.draw(sprite);
	}

private:
};