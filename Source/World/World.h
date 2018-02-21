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
		floor({  1280.f, 720.f / 2.f + 100.f }, { 1280.f / 2.f  , 720.f / 2.f }),
		frontCurtain(0.f),
		midCurtain( floor.getSize().y),
		backCurtain( floor.getSize().y + 150.f ),
		perspective(floor, { 0.f, 360.f })
	{
	}

	void addEntity(EntityPtr entity)
	{
		entities.emplace_back(std::move(entity));

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

			perspective.applyTo(frontCurtain, true);
			perspective.applyTo(midCurtain, true);
			perspective.applyTo(backCurtain, true);
			
			perspectiveFactorChanger();
		}
		else
		{
			applyAbsolutePosToAllEntities();

			applyAbsolutePos(frontCurtain);
			applyAbsolutePos(midCurtain);
			applyAbsolutePos(backCurtain);
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
			const auto targetPos = entities[indexOfFollowedEntity]->getPosition();

			const auto floorPos = floor.getPosition();

			mainCamera.setPosition({ (targetPos + floorPos).x, floorPos.y - 720.f / 2.f });
		}
	}

	Floor floor;

	Perspective perspective;

	size_t indexOfFollowedEntity = -1;

	std::vector<EntityPtr> entities;

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
			perspective.removeFrom(*entity);
		}
	}

	void updateAllEntities(float dt)
	{
		for (auto& entity : entities)
		{
			entity->update(dt);
		}
	}

	void applyPerspectiveToAllEntities()
	{
		for (auto& entity : entities)
		{
			perspective.applyTo(*entity);
		}
	}


	void applyAbsolutePosToAllEntities()
	{
		for (auto& entity : entities)
		{
			applyAbsolutePos(*entity);
		}
	}

	void applyAbsolutePos(Entity& entity)
	{
		auto& sprite = entity.getObject();

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
			entity->render(renderer);
		}
	}


	void handleBoundingForAllEntities()
	{
		for (auto& entity : entities)
		{
			floor.handleBounding(*entity);
		}
	}

	void perspectiveFactorChanger()
	{
		float factor = perspective.getPerspectiveFactor();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			perspective.setFactor(factor - 1.5f);
			std::cout << factor << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			perspective.setFactor(factor + 1.5f);
			std::cout << factor << std::endl;
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
		
		const float height = curtain.getDistance();
		const float yFactor = perspective.getYFactor({ 0.f, -height });

		float camShiftX = getCamShift().x;
		auto& sprite = curtain.getObject();
		const auto spritePos = sprite.getPosition();

		float spriteShiftX = camShiftX - camShiftX * (yFactor);

		const sf::Vector2f finalSpritePos = sf::Vector2f( spritePos.x + spriteShiftX, spritePos.y );

		sprite.setPosition(finalSpritePos);
		
	}

	void handleTransparent(Curtain& curtain, Entity& entity)
	{

	}

	sf::Vector2f getCamShift() const
	{
		return mainCamera.getPosition() - floor.getPosition();
	}

};