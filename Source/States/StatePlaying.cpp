#include "StatePlaying.h"

#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../GUI/Icon.h"
#include "../Game.h"

#include "../Objects/Hero.h"
#include "../Objects/TestFurniture.h"

#include <iostream>

std::string test;

StatePlaying::StatePlaying(Game& game)
	:
	StateBase(game),
	testMenu(game.getWindow()),
	spellMenuTest({ 300, 300 }, heroTest),
	anotherHead(10.f),
	inv({ 2, 2 })
{
	{
		auto f = [&]() mutable {
			std::cout << testString << '\n';
			clicked = !clicked;
		};
		addButton("Print", f);

		auto hide = [&]() {
			guiIsHidden = !guiIsHidden;
		};
		addButton("Hide", hide);

		auto exit = [&]() {
			game.close();
		};

		addButton("Exit", exit);

		auto textBox = std::make_unique<gui::TextBox>(testString);
		testMenu.addWidget(std::move(textBox));

		auto hpIcon = gui::make_icon(hp, maxHP);
		hpIcon->setTextureBackground(ResourceHolder::get().textures.acquire("icon_circle"));
		hpIcon->setColor(sf::Color::Blue);
		testMenu.addWidget(std::move(hpIcon));
	}

	{
		heroTest.debugPrintArmor();

		heroTest.addHead(anotherHead);

		heroTest.debugPrintArmor();

		heroTest.addHead(Armor(14));
		heroTest.debugPrintArmor();


		auto item = makeItem();
		item->setTexture("test_item");
		inv.addItem(std::move(item));

		auto item1 = makeItem();
		item1->setTexture("test_item1");
		inv.addItem(std::move(item1));

		auto item2 = makeItem();
		item2->setTexture("test_item2");
		inv.addItem(std::move(item2));
	}


	auto furn = std::make_unique<TestFurniture>();
	testWorld.addObject(std::move(furn));

	auto en = makeTestHero();
	testWorld.addObject(std::move(en));

}

void StatePlaying::handleEvent(sf::Event e)
{
	if (!guiIsHidden)
	{
		testMenu.handleEvent(e, gamePtr->getWindow());
		spellMenuTest.handleEvent(e, gamePtr->getWindow());
		inv.handleEvent(e, gamePtr->getWindow());
	}

	testWorld.handleEvent(e, gamePtr->getWindow());

	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Escape:
			guiIsHidden = !guiIsHidden;
			break;
		default:
			break;
		}
	}
}

void StatePlaying::handleInput()
{
	if (!guiIsHidden)
	{
		inv.handleInput(gamePtr->getWindow());

	}
}

void StatePlaying::update(sf::Time deltaTime)
{
	float dt = deltaTime.asSeconds();

	if (!guiIsHidden)
	{
		testMenu.update(dt);
		spellMenuTest.update(dt);
		inv.update(dt);
	}
	
	hp -= 0.17f;
	if (hp < 0.f)
	{
		hp = maxHP;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(gamePtr->getWindow());

	testWorld.update(dt);
	
	/*
	float debugFPS = 1.f / dt;
	if(debugFPS < 60.f) std::cout << "Debug FPS: " << debugFPS << std::endl;
	*/
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer) const
{
	testWorld.render(renderer);


	if (!guiIsHidden)
	{
		testMenu.render(renderer);
		spellMenuTest.render(renderer);
		inv.render(renderer);
	}
	
	
}
