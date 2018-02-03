#pragma once

#include "../Spells/Effect.h"

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


private:

	std::vector<Modifier> mods;
};