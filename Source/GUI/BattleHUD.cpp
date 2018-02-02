#include "BattleHUD.h"


namespace gui
{
	BattleHUD::SkillsContainer::SkillsContainer(const sf::Vector2f & position)
	{
		background.setPosition(position);
		baseSize = { padding, padding } + iconSize;

	}
}