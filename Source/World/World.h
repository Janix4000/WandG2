#pragma once

#include "../Objects/Entity.h"
#include "Floor.h"

class World
{
public:

	World()
		:
		floor({ 1280.f, 720.f / 2.f - 100 }, { 1280.f / 2.f  , 720.f / 2.f })
	{}

	void addEntity(Entity& entity)
	{
		entities.emplace_back(entity);
	}

	void update(float dt)
	{
		updateAllEntities(dt);

		handleBoundingForAllEntities();
		applyParalaxToAllEntities();
	}

	void render(sf::RenderTarget& renderer) const
	{
		floor.render(renderer);
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
		return entity.getPosition() - floor.getPosition() ;
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

	void handleBoundingForAllEntities()
	{
		for (auto& entity : entities)
		{
			handleBoundindg(entity);
		}
	}

	void handleBoundindg(Entity& entity)
	{
		const auto shapeSize = floor.getSize();
		const auto shapePos = floor.getPosition();

		const auto pos = entity.getPosition();
		const auto size = entity.getSize();

		const auto sR = shapePos.x + shapeSize.x / 2;
		const auto sL = shapePos.x - shapeSize.x / 2;
		const auto sT = shapePos.y - shapeSize.y;
		const auto sB = shapePos.y;

		const auto R = pos.x + size.x / 2;
		const auto L = pos.x - size.x / 2;
		const auto T = pos.y;   // -size.y;
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

		entity.move(shift);

	}

};