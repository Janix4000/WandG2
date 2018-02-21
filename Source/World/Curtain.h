#pragma once

#include "Floor.h"
#include "../ResourceManager/ResourceHolder.h"

class Curtain
{
public:
	Curtain(float height)
		:
		height(height), 
		pos(0.f, height)
	{
		texture = ResourceHolder::get().textures.acquire("background2");
		background.setTexture(*texture);

		const auto textureSize = texture->getSize();
		background.setOrigin(float(textureSize.x) / 2.f, float(textureSize.y));
	}

	Curtain(float height, sf::Vector2f pos)
		:
		Curtain(height) 
	{
		this->pos = pos;
	}

	void render(sf::RenderTarget& renderer) const
	{
		renderer.draw(background);
	}




	sf::Sprite& getSprite()
	{
		return background;
	}

	float getHeight() const
	{
		return height;
	}

	sf::Vector2f getPosition() const
	{
		return pos;
	}



private:

	sf::Vector2f pos;
	float height;
	
	TexturePtr texture;
	sf::Sprite background;
};