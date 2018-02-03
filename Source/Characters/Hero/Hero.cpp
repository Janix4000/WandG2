#include "Hero.h"



MainHero::MainHero()
{
	spells.emplace_back(SpellBase("fireball"));
	spells.emplace_back(SpellBase("waterwave"));

	texture = (ResourceHolder::get().textures.acquire("man"));
	sprite.setTexture(*texture);
}


MainHero::~MainHero()
{
}
