#pragma once

#include "../Objects/Entity.h"
#include "Floor.h"
#include "Camera.h"
#include "Curtain.h"
#include "Perpective.h"

class World
{
public:

	World()
		:
		floor({  1280.f, 720.f + 100.f }, { 1280.f / 2.f  , 720.f / 2.f }),
		frontCurtain(0.f),
		midCurtain(-floor.getPosition().y),
		backCurtain(-(floor.getPosition().y + 200.f)),
		perspective(floor, { 0.f, 520.f })
	{
	}

	void addEntity(Entity& entity)
	{
		entities.emplace_back(entity);

		indexOfFollowedEntity = entities.size() - 1;
	}

	void update(float dt)
	{
		updateAllEntities(dt);

		handleBoundingForAllEntities();

		if (isPerspectiveHandled)
		{
			applyPerspectiveToAllEntities();
			perspective.applyToFloor();
			perspectiveFactorChanger();
		}
		else
		{
			applyAbsolutePosToAllEntities();
		}


		handleCameraFollowing();
		handleCurtainsParalax();
	}

	void render(sf::RenderTarget& renderer) const
	{
		mainCamera.applyToWindow(renderer);

		

		floor.render(renderer);
		backCurtain.render(renderer);
		midCurtain.render(renderer);

		renderAllEntities(renderer);

		frontCurtain.render(renderer);

	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		//const auto mousePos = mainCamera.getMousePosition(window);

		//floor.setPos({ float(mousePos.x), float(mousePos.y) }); 

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

	Camera mainCamera;

	void handleCameraFollowing()
	{
		if (indexOfFollowedEntity != -1)
		{
			const auto targetPos = entities[indexOfFollowedEntity].getPosition();

			const auto floorPos = floor.getPosition();

			mainCamera.setPosition({ (targetPos + floorPos).x, floorPos.y - 720.f / 2.f });
		}
	}

	Floor floor;

	Perspective perspective;

	float perspectiveFactor;

	int indexOfFollowedEntity = -1;

	std::vector<Entity> entities;

	bool isPerspectiveHandled = true;

	void switchPerspectiveHandling()
	{
		isPerspectiveHandled = !isPerspectiveHandled;

		if (!isPerspectiveHandled)
		{
			removePerspectiveFromAllEntities();
			perspective.removeFromFloor();
		}
	}

	void removePerspectiveFromAllEntities()
	{
		for (auto& entity : entities)
		{
			perspective.removeFrom(entity);
		}
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
			perspective.applyTo(entity);
		}
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
			floor.handleBounding(entity);
		}
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

	Curtain frontCurtain;
	Curtain midCurtain;
	Curtain backCurtain;

	void handleCurtainsParalax()
	{
		handleParalax(frontCurtain);
		handleParalax(midCurtain);
		handleParalax(backCurtain);
	}

	void handleParalax(Curtain& curtain)
	{
		const float height = curtain.getHeight();
		const float yFactor = perspective.getYFactor({ 0.f, height });

		float camShiftX = getCamShift().x;

		auto& sprite = curtain.getSprite();

		const sf::Vector2f finalSpritePos = sf::Vector2f( -camShiftX * yFactor, height * yFactor ) + floor.getPosition();

		sprite.setPosition(finalSpritePos);

	}

	sf::Vector2f getCamShift() const
	{
		return mainCamera.getPosition() - floor.getPosition();
	}

};