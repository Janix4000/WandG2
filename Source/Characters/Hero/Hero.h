#pragma once

#include "../../Spells/SpellBase.h"
#include "../../Armor/Armor.h"

#include <iostream>

using SpellVector = std::vector<SpellBase>;



class MainHero
{
private:
	class Statistics
	{
	public:
		Statistics()
		{
			stats.emplace_back(Stat(StatType::Strength));
			stats.emplace_back(Stat(StatType::Armor));
		}

		float getValue(StatType type)const
		{
			const auto foundStat = std::find_if(stats.begin(), stats.end(), [&](const auto& stat) {
				return stat.getType() == type;
			});
			if(foundStat != stats.end())
			return foundStat->getValue();
			else return -1;
		}

		void applyMods(const std::vector<Modifier>& mods)
		{
			for (const auto& mod : mods)
			{
				for (auto& stat : stats)
				{
					if (mod.target == stat.getType())
					{
						stat.addModifier(mod);
						break;
					}
				}
			}
		}
		void applyModifier(const Modifier& mod)
		{
			std::vector<Modifier> mods(1, mod);
			applyMods(mods);
		}

		void removeMods(const std::vector<Modifier>& mods)
		{
			for (const auto& mod : mods)
			{
				for (auto& stat : stats)
				{
					if (mod.target == stat.getType())
					{
						stat.removeModifier(mod);
						break;
					}
				}
			}
		}
		void removeModifier(const Modifier& mod)
		{
			std::vector<Modifier> mods(1, mod);
			removeMods(mods);
		}
		
	private:
		std::vector<Stat> stats;
	};
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
			stats.removeModifier(head.getEffects());
		}
		head = h;
		stats.applyModifier(head.getEffects());
		hasArmor = true;
	}

	void debugPrintArmor() const
	{
		std::cout << "Armor: " << stats.getValue(StatType::Armor) << "\n";
	}

	void setPosition(sf::Vector2f position)
	{
		pos = position;
		sprite.setPosition(pos);
	}

private:

	SpellVector spells;
	Statistics stats;


	Armor head;
	bool hasArmor = false;


	TexturePtr texture;
	sf::Sprite sprite;

	sf::Vector2f pos;
};
