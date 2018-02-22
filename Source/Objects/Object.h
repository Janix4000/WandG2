#pragma once

#include "Entity.h"


class Object
	:
	public Entity
{
public:

	Object()
		:
		Entity()
	{
		ID = numberOfEntities++;
	}

	virtual void update(float dt) = 0;
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
	virtual void handleInput(const sf::RenderWindow& window) = 0;
	void render(sf::RenderTarget& renderer) const = 0;


	virtual sf::Transformable& getObject() override
	{
		return sprite;
	}
	virtual sf::Vector2f getSize() const override
	{
		return sf::Vector2f(texture->getSize());
	}

	void setTexture(TexturePtr newTexture)
	{
		texture = newTexture;
		sprite.setTexture(*texture);

		const auto size = getSize();
		sprite.setOrigin(size.x / 2.f, size.y);
	}

	sf::Sprite& getSprite()
	{
		return sprite;
	}

	int getID() const
	{
		return ID;
	}

private:

	TexturePtr texture;

	static int numberOfEntities;
	int ID;

protected:
	sf::Sprite sprite;
};

using ObjectPtr = std::unique_ptr<Object>;
