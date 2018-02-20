#pragma once

#include "../Objects/Entity.h"

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

	void applyToWindow(sf::RenderTarget& window) const
	{
		window.setView(cam);
	}
private:

	sf::View cam;
};