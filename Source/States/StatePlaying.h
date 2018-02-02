#ifndef STATEPLAYING_H_INCLUDED
#define STATEPLAYING_H_INCLUDED

#include "StateBase.h"
#include "../GUI/StackMenu.h"
#include "../GUI/Menu.h"

#include "../GUI/BattleHUD.h"


class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleEvent(sf::Event e) override;

        void handleInput() override;

        void update(sf::Time deltaTime) override;

        void fixedUpdate(sf::Time deltaTime) override;

        void render(sf::RenderTarget& renderer)	override;

    private:
        gui::Menu testMenu;
		std::string testString = "bg";
		bool clicked = false;

		bool hidden = false;

		float maxHP = 50;
		float hp = maxHP;

		Armor anotherHead;
		MainHero heroTest;
		gui::SpellMenu spellMenuTest;
};

#endif // STATEPLAYING_H_INCLUDED
