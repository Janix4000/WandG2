#pragma once

#include "../Spells/Effect.h"

class Armor
{
public:
	Armor(float armor = 5.f)
		:
		armorModif(armor, StatType::Armor)
	{
	}


	const Modifier& getEffects() const
	{
		return armorModif;
	}


private:
	Modifier armorModif;


};