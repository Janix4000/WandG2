#pragma once

#include "../Spells/Effect.h"
#include "../../ResourceManager/ResourceHolder.h"

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

	void setTexture(TexturePtr t)
	{
		texture = t;
	}

private:

	std::vector<Modifier> mods;
	TexturePtr texture;
};