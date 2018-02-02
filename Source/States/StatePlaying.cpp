#include "StatePlaying.h"

#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../GUI/Icon.h"
#include "../Game.h"

#include <iostream>

std::string test;

StatePlaying::StatePlaying(Game& game)
	:
	StateBase(game),
	testMenu(game.getWindow()),
	spellMenuTest({ 300, 300 }, heroTest),
	anotherHead(10.f)
{
	{
		auto b = gui::make_button();
		b->setTexture(ResourceHolder::get().textures.acquire("button1"));
		b->setText("Start");
		b->setFunction([&]() mutable {
			std::cout << testString << '\n';
			clicked = !clicked;
		});

		testMenu.addWidget(std::move(b));

		auto b2 = gui::make_button();
		b2->setTexture(ResourceHolder::get().textures.acquire("button1"));
		b2->setText("Exit");
		b2->setFunction([&]() mutable {
			game.close();
		});

		testMenu.addWidget(std::move(b2));

		auto textBox = std::make_unique<gui::TextBox>(testString);
		testMenu.addWidget(std::move(textBox));

		auto hpIcon = gui::make_icon(hp, maxHP);
		hpIcon->setTextureBackground(ResourceHolder::get().textures.acquire("icon_circle"));
		hpIcon->setColor(sf::Color::Blue);
		testMenu.addWidget(std::move(hpIcon));
	}

	heroTest.debugPrintArmor();

	heroTest.addHead(anotherHead);

	heroTest.debugPrintArmor();

	heroTest.addHead(Armor(14));
	heroTest.debugPrintArmor();

}

void StatePlaying::handleEvent(sf::Event e)
{
	if (!hidden)
	{
		testMenu.handleEvent(e, gamePtr->getWindow());
	}

	spellMenuTest.handleEvent(e, gamePtr->getWindow());

	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
			hidden = !hidden;
			break;
		default:
			break;
		}
	}
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(sf::Time deltaTime)
{
	if (!hidden)
	{
		testMenu.update(deltaTime.asSeconds());
	}
	spellMenuTest.update(deltaTime.asSeconds());


	hp -= 0.07f;
	if (hp < 0.f) hp = maxHP;
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer)
{
	if (!hidden)
	{
		testMenu.render(renderer);
	}

	spellMenuTest.render(renderer);
}
