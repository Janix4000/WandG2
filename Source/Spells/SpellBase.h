#pragma once

#include <functional>

#include "../ResourceManager/ResourceHolder.h"

class Entity;

class SpellData
{
public:
	std::string name;
	int manaCost;
};

class SpellBase
{
public:

	SpellBase(const std::string& name);
	~SpellBase();
	
	const TexturePtr getTexture() const;
	const SpellData& getInfo() const;

private:
	TexturePtr spellIcon;
	static std::string foldername;

	SpellData info;

	std::function<void(Entity& target)> effect = [](Entity& target) {};
};

