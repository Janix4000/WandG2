#pragma once

#include "../../Spells/SpellBase.h"
#include "../../Armor/Armor.h"

#include <iostream>

using SpellVector = std::vector<SpellBase>;



class MainHero
{
public:
	MainHero();
	~MainHero();

	const SpellVector& getSpells() const
	{
		return spells;
	}

	void addHead(Armor h)
	{
		if (hasArmor)
		{
			armor.removeModifier(head.getEffects());
		}
		head = h;
		armor.addModifier(head.getEffects());
		hasArmor = true;
	}

	void debugPrintArmor() const
	{
		std::cout << "Armor: " << armor.getValue() << "\n";
	}

	void setPosition(sf::Vector2f position)
	{
		pos = position;
		sprite.setPosition(pos);
	}

private:

	SpellVector spells;
	Stat armor;

	Armor head;
	bool hasArmor = false;

	TexturePtr texture;
	sf::Sprite sprite;

	sf::Vector2f pos;
};
