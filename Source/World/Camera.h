#pragma once

#include "../Objects/Entity.h"
#include "../Objects/FreePhysic.h"

class Camera
{
public:

	Camera()
	{
		cam.setSize(1280.f, 720.f);
	}

	void setPosition(const sf::Vector2f& position)
	{
		cam.setCenter(position);
	}

	sf::Vector2f getPosition() const
	{
		return cam.getCenter();
	}

	void applyToWindow(sf::RenderTarget& window) const
	{
		window.setView(cam);
	}
	
	sf::Vector2f getMousePosition(const sf::RenderWindow& window) const
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		return window.mapPixelToCoords(pixelPos);
	}
	
private:

	sf::View cam;
	FreePhysic physic;
};