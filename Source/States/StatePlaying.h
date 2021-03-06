#ifndef STATEPLAYING_H_INCLUDED
#define STATEPLAYING_H_INCLUDED


#include "StateBase.h"
#include "../GUI/StackMenu.h"
#include "../GUI/Menu.h"

#include "../GUI/BattleHUD.h"
#include "../Inventory/Inventory.h"

#include "../World/World.h"


class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleEvent(sf::Event e) override;

        void handleInput() override;

        void update(sf::Time deltaTime) override;

        void fixedUpdate(sf::Time deltaTime) override;

        void render(sf::RenderTarget& renderer) const override;

    private:
        gui::Menu testMenu;
		std::string testString = "bg";
		bool clicked = false;

		bool guiIsHidden = false;

		float maxHP = 50;
		float hp = maxHP;

		Armor anotherHead;
		MainHero heroTest;
		gui::SpellMenu spellMenuTest;

		Inventory inv;

		//Floor floor;
		//Entity testEntity;

		World testWorld;

private:
	void addButton(const std::string text, std::function<void()> function, std::string textureName = "button1")
	{
		auto newButton = gui::make_button();

		newButton->setTexture(ResourceHolder::get().textures.acquire(textureName));
		newButton->setText(text);
		newButton->setFunction(function);

		testMenu.addWidget(std::move(newButton));
	}
};

#endif // STATEPLAYING_H_INCLUDED
