#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include <SFML/System/NonCopyable.hpp>


class ResourceHolder 
	:
	public sf::NonCopyable
{
public:
	static ResourceHolder& get()
	{
		static ResourceHolder holder;
		return holder;
	}

	FontManager fonts;
	TextureManager textures;
	SoundBufferManager soundBuffers;

private:
	ResourceHolder()
		: 
		fonts("fonts", "ttf")
		, textures("txrs", "png")
		, soundBuffers("sfx", "ogg")
	{
	}
};

using TexturePtr = std::shared_ptr<sf::Texture>;
using FontPtr = std::shared_ptr<sf::Font>;
using SoundBufferPtr = std::shared_ptr<sf::SoundBuffer>;


