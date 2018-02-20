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

		if (isPerspectiveHandled)
		{
			applyPerspectiveToAllEntities();
			applyPerspectiveToFloor();
			perspectiveFactorChanger();
		}
		else
		{
			applyAbsolutePosToAllEntities();
		}
	}

	void render(sf::RenderTarget& renderer) const
	{
		floor.render(renderer);
		renderAllEntities(renderer);
	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		const auto mousePos = sf::Mouse::getPosition(window);

		floor.setPos({ float(mousePos.x), float(mousePos.y) });

		switch (e.type)
		{
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				switchPerspectiveHandling();
			}
			break;
		default:
			break;
		}
	}

	void handleInput()
	{}

private:
	Floor floor;

	float yFactor = 1.f;
	float perspectiveFactor = 300.f;

	std::vector<Entity> entities;

	bool isPerspectiveHandled = true;

	void switchPerspectiveHandling()
	{
		isPerspectiveHandled = !isPerspectiveHandled;

		if (!isPerspectiveHandled)
		{
			removePerspectiveFromAllEntities();
			removePerspectiveFromFloor();
		}
	}

	void removePerspectiveFromAllEntities()
	{
		for (auto& entity : entities)
		{
			removePerspective(entity);
		}
	}

	void removePerspective(Entity& entity)
	{
		auto& sprite = entity.getSprite();

		sprite.setScale(1.f, 1.f);
	}

	void removePerspectiveFromFloor()
	{
		auto& shape = floor.getShape();

		shape.setScale(1.f, 1.f);
	}

	void updateAllEntities(float dt)
	{
		for (auto& entity : entities)
		{
			entity.update(dt);
		}
	}

	void applyPerspectiveToAllEntities()
	{
		for (auto& entity : entities)
		{
			applyPerspective(entity);
		}
	}

	void applyPerspective(Entity& entity)
	{
		auto& sprite = entity.getSprite();

		const auto pos = entity.getPosition();
		const float yFactor = getYFactor(pos);

		const auto factoredPosition = getPerspectivePosition(pos, yFactor);

		sprite.setPosition(factoredPosition);
		sprite.setScale(yFactor, yFactor);
	}

	float getYFactor(const sf::Vector2f& pos) const 
	{
		return perspectiveFactor / (perspectiveFactor - pos.y);
	}

	sf::Vector2f getPerspectivePosition(const sf::Vector2f& pos, float yFactor) const
	{
		return floor.getPosition() + sf::Vector2f(pos.x, pos.y * yFactor);
	}

	void applyPerspectiveToFloor()
	{
		const float yFactor = getYFactor(-floor.getSize());
		floor.getShape().setScale(1.f, yFactor);
	}

	void applyAbsolutePosToAllEntities()
	{
		for (auto& entity : entities)
		{
			applyAbsolutePos(entity);
		}
	}

	void applyAbsolutePos(Entity& entity)
	{
		auto& sprite = entity.getSprite();

		const auto absPos = getAbsoloutePos(entity);

		sprite.setPosition(absPos);
	}

	sf::Vector2f getAbsoloutePos(const Entity& entity)
	{
		return entity.getPosition() + floor.getPosition();;
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
		const auto floorSize = floor.getSize();

		const auto pos = entity.getPosition();
		const auto size = entity.getSize();

		const auto fR = 0.f + floorSize.x / 2;
		const auto fL = 0.f - floorSize.x / 2;
		const auto fT = 0.f - floorSize.y;
		const auto fB = 0.f;

		const auto R = pos.x + size.x / 2;
		const auto L = pos.x - size.x / 2;
		const auto T = pos.y;   // -size.y;
		const auto B = pos.y;

		sf::Vector2f shift;

		if (R >= fR)
		{
			shift.x += fR - R;
		}
		if (L <= fL)
		{
			shift.x += fL - L;
		}
		if (B >= fB)
		{
			shift.y += fB - B;
		}
		if (T <= fT)
		{
			shift.y += fT - T;
		}

		entity.move(shift);

	}

	void perspectiveFactorChanger()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			perspectiveFactor -= 0.5f;
			std::cout << perspectiveFactor << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			perspectiveFactor += 0.5f;
			std::cout << perspectiveFactor << std::endl;
		}
	}

};