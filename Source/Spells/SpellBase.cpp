#include "SpellBase.h"



std::string SpellBase::foldername = "spells/";


SpellBase::SpellBase(const std::string & name)
{
	info.name = name;
	spellIcon = ResourceHolder::get().textures.acquire(foldername + name);
	info.manaCost = 6;
}

SpellBase::~SpellBase()
{
}

const TexturePtr SpellBase::getTexture() const
{
	return spellIcon;
}

const SpellData & SpellBase::getInfo() const
{
	return info;
}
