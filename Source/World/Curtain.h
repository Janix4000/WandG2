#pragma once

#include "Floor.h"
#include "../ResourceManager/ResourceHolder.h"
#include "../Objects/Entity.h"

class Curtain
	:
	public Entity
{
public:
	Curtain(float distance)
		:
		distance(distance)
	{
		assert(distance >= 0.f);
		setPosition({ 0.f, -distance });
		texture = ResourceHolder::get().textures.acquire("background2");
		background.setTexture(*texture);

		const auto textureSize = texture->getSize();
		background.setOrigin(float(textureSize.x) / 2.f, float(textureSize.y));

	}

	Curtain(float distance, float posY)
		:
		Curtain(distance)
	{
		if (posY > 0.f) posY = -posY;

		assert(distance >= - posY);
		setPosition({0.f, posY});
	}

	virtual void update(float dt) override
	{}
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) override
	{}
	virtual void handleInput(const sf::RenderWindow& window) override
	{}
	virtual void render(sf::RenderTarget& renderer) const override
	{
		renderer.draw(background);
	}

	virtual sf::Transformable& getObject() override
	{
		return background;
	}
	virtual sf::Vector2f getSize() const override
	{
		const auto size = texture->getSize();
		return { float(size.x), float(size.y) };
	}

	float getDistance() const
	{
		return distance;
	}

private:
	float distance;
	
	TexturePtr texture;
	sf::Sprite background;
};