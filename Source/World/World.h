#pragma once

#include "../Objects/Entity.h"
#include "Floor.h"

class World
{
public:

	void addEntity(Entity& entity)
	{
		entities.emplace_back(entity);
	}

	void update(float dt)
	{
		updateAllEntities(dt);
		applyParalaxToAllEntities();
	}

	void render(sf::RenderTarget& renderer) const
	{
		renderAllEntities(renderer);
	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{}

	void handleInput()
	{}

private:
	Floor floor;

	float yFactor = 1.f;
	float paralaxFactor = 300.f;

	std::vector<Entity> entities;

	void updateAllEntities(float dt)
	{
		for (auto& entity : entities)
		{
			entity.update(dt);
		}
	}

	void applyParalaxToAllEntities()
	{
		for (auto& entity : entities)
		{
			applyParalax(entity);
		}
	}


	void applyParalax(Entity& entity)
	{
		auto& sprite = entity.getSprite();

		const auto shift = getShift(entity);
		const float yFactor = getYFactor(shift);

		const auto factoredPosition = getFactoredPosition(shift, yFactor);

		sprite.setPosition(factoredPosition);
	}

	sf::Vector2f getShift(const Entity& entity) const 
	{
		return floor.getPosition() - entity.getPosition();
	}

	float getYFactor(const sf::Vector2f& shift) const 
	{
		return paralaxFactor / (shift.y + paralaxFactor);
	}

	sf::Vector2f getFactoredPosition(const sf::Vector2f& shift, float yFactor) const
	{
		return floor.getPosition() + sf::Vector2f(shift.x, shift.y * yFactor);
	}

	void renderAllEntities(sf::RenderTarget& renderer) const
	{
		for (auto& entity : entities)
		{
			entity.render(renderer);
		}
	}

};