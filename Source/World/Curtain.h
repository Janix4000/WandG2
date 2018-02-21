#pragma once

#include "Floor.h"
#include "../ResourceManager/ResourceHolder.h"

class Curtain
{
public:
	Curtain(float height)
		:
		height(height)
	{
		texture = ResourceHolder::get().textures.acquire("background2");
		background.setTexture(*texture);

		const auto textureSize = texture->getSize();
		background.setOrigin(textureSize.x / 2.f, textureSize.y);
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



private:

	float height;
	
	TexturePtr texture;
	sf::Sprite background;
};