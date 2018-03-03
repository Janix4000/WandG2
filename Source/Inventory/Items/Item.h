#pragma once

#include "../../Spells/Effect.h"
#include "../../ResourceManager/ResourceHolder.h"
#include "SFML/Graphics.hpp"

class Item
{
public:
	enum class Type
	{
		Armor,
		Weapon,
		Count
	};

public:
	Item() = default;

	Item(Item&& other) noexcept = default;

	TexturePtr getTexture() const
	{
		return texture;
	}

	void setTexture(const std::string& textureName)
	{
		auto t = ResourceHolder::get().textures.acquire(textureName);
		setTexture(t);
	}

	void setTexture(TexturePtr t)
	{
		texture = t;
		sprite.setTexture(*texture);
	}

	void draw(sf::RenderTarget& renderer)
	{
		renderer.draw(sprite);
	}

	void setPosition(const sf::Vector2f& position)
	{
		pos.x = position.x;
		pos.y = position.y;
		sprite.setPosition(pos);
	}

private:

	std::vector<Modifier> mods;
	TexturePtr texture;
	sf::Sprite sprite;

	sf::Vector2f pos;
};

using ItemPtr = std::unique_ptr<Item>;

inline ItemPtr makeItem()
{
	return std::make_unique<Item>();
}