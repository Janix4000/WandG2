#pragma once

#include "../Objects/Object.h"
#include "Floor.h"
#include "Camera.h"
#include "Curtain.h"
#include "Perpective.h"

class World
{
public:

	World()
		:
		floor({  2.f * 1280.f, 720.f / 2.f + 100.f }, { 1280.f / 2.f  , 720.f / 2.f }),
		frontCurtain(0.f),
		midCurtain( floor.getSize().y),
		backCurtain( floor.getSize().y + 150.f ),
		perspective(floor, { 0.f, 360.f })
	{
	}

	void addObject(ObjectPtr object)
	{
		objects.emplace_back(std::move(object));

		setCameraTarget(int(objects.size() - 1));
	}

	void update(float dt)
	{
		updateAllObjects(dt);
		handleBoundingForAllObjects();

		mainCamera.update(dt);

		if (isPerspectiveHandled)
		{
			applyPerspectiveToAllObjects();
			perspective.applyToFloor();

			perspective.applyTo(frontCurtain, true);
			perspective.applyTo(midCurtain, true);
			perspective.applyTo(backCurtain, true);
			
			perspectiveFactorChanger();
		}
		else
		{
			applyAbsolutePosToAllObjects();

			applyAbsolutePos(frontCurtain);
			applyAbsolutePos(midCurtain);
			applyAbsolutePos(backCurtain);
		}

		frontCurtain.handleTransparency(getObjectByID(followedObjectID));

		handleCameraFollowing();
		handleCurtainsParalax();

		sortAllObjectsByDist();
	}

	void render(sf::RenderTarget& renderer) const
	{
		mainCamera.applyToWindow(renderer);

		

		floor.render(renderer);
		backCurtain.render(renderer);
		midCurtain.render(renderer);

		renderAllObjects(renderer);

		frontCurtain.render(renderer);

	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		//const auto mousePos = mainCamera.getMousePosition(window);

		//floor.setPos({ float(mousePos.x), float(mousePos.y) }); 

		debugCameraSwitch(e);


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
	int followedObjectID = -1;

	void handleCameraFollowing()
	{
		if (followedObjectID != -1)
		{
			const auto targetPos = getObjectByID(followedObjectID).getPosition();

			const auto floorPos = floor.getPosition();

			mainCamera.setPosition({ (targetPos + floorPos).x, floorPos.y - 720.f / 2.f });
		}
		else
		{
			mainCamera.free();
		}
	}

	void setCameraTarget(int ID)
	{
		if (ID != followedObjectID)
		{
			mainCamera.free();
			followedObjectID = ID;
		}
	}

	sf::Vector2f getCamShift() const
	{
		return mainCamera.getPosition() - floor.getPosition();
	}


	Floor floor;

	Perspective perspective;
	bool isPerspectiveHandled = true;

	void switchPerspectiveHandling()
	{
		isPerspectiveHandled = !isPerspectiveHandled;

		if (!isPerspectiveHandled)
		{
			removePerspectiveFromAllObjects();
			perspective.removeFromFloor();
		}
	}

	void removePerspectiveFromAllObjects()
	{
		for (auto& object : objects)
		{
			perspective.removeFrom(*object);
		}
	}


	std::vector<ObjectPtr> objects;

	void updateAllObjects(float dt)
	{
		for (auto& object : objects)
		{
			object->update(dt);
		}
	}

	Object& getObjectByID(int ID)
	{
		auto found = std::find_if(objects.begin(), objects.end(), [&](const auto& object) {
			return object->getID() == ID;
		});

		assert(found != objects.end());

		return **found;
	}

	void sortAllObjectsByDist()
	{
		const auto isFurther = [](ObjectPtr& lhs, ObjectPtr& rhs) {

			return lhs->getPosition().y < rhs->getPosition().y;
		};

		std::sort(objects.begin(), objects.end(), isFurther);
	}

	void applyPerspectiveToAllObjects()
	{
		for (auto& object : objects)
		{
			perspective.applyTo(*object);
		}
	}

	void applyAbsolutePosToAllObjects()
	{
		for (auto& object : objects)
		{
			applyAbsolutePos(*object);
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


	void renderAllObjects(sf::RenderTarget& renderer) const
	{
		for (auto& object : objects)
		{
			object->render(renderer);
		}
	}


	void handleBoundingForAllObjects()
	{
		for (auto& object : objects)
		{
			floor.handleBounding(*object);
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


	void debugCameraSwitch(sf::Event e)
	{
		if (e.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				int newID = followedObjectID + 1;
				if (newID == objects.size())
				{
					newID = 0;
				}
				setCameraTarget(newID);
			}
		}
	}

};