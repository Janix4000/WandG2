#pragma once

#include <memory>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../ResourceManager/ResourceHolder.h"

#include "../Utility/Vec3.h"

class Entity
{

private:
	sf::Vector2f pos;
	sf::Vector2f size;

	//sf::Sprite sprite;
	//TexturePtr texture;

	//float speed = 250.f;

public:

	Entity()
	{
		setPosition({0.f, -1.f });
		ID = numberOfEntities++;
	}

	virtual ~Entity() = default;

	virtual void update(float dt) = 0;
	virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
	virtual void handleInput(const sf::RenderWindow& window) = 0;
	virtual void render(sf::RenderTarget& renderer) const = 0;
		
	virtual sf::Transformable& getObject() = 0;
	virtual sf::Vector2f getSize() const = 0;


	void setPosition(sf::Vector2f position)
	{
		pos = position;
	}
	const sf::Vector2f& getPosition() const
	{
		return pos;
	}
	void move(sf::Vector2f shift)
	{
		setPosition(getPosition() + shift);
	}

	int getID() const
	{
		return ID;
	}
	
private:
	static int numberOfEntities;
	int ID;

protected:
	
};


using EntityPtr = std::unique_ptr<Entity>;