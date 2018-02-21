#include "StatePlaying.h"

#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../GUI/Icon.h"
#include "../Game.h"
#include "../Objects/Hero.h"

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

	{
		heroTest.debugPrintArmor();

		heroTest.addHead(anotherHead);

		heroTest.debugPrintArmor();

		heroTest.addHead(Armor(14));
		heroTest.debugPrintArmor();


		auto item = std::make_unique<Item>();
		item->setTexture(ResourceHolder::get().textures.acquire("test_item"));
		inv.addItem(std::move(item));

		auto item1 = std::make_unique<Item>();
		item1->setTexture(ResourceHolder::get().textures.acquire("test_item1"));
		inv.addItem(std::move(item1));

		auto item2 = std::make_unique<Item>();
		item2->setTexture(ResourceHolder::get().textures.acquire("test_item2"));
		inv.addItem(std::move(item2));
	}

	
	auto en = makeTestHero();

	testWorld.addEntity(std::move(en));
	
}

void StatePlaying::handleEvent(sf::Event e)
{
	if (!hidden)
	{
		testMenu.handleEvent(e, gamePtr->getWindow());
	}

	spellMenuTest.handleEvent(e, gamePtr->getWindow());

	inv.handleEvent(e, gamePtr->getWindow());

	testWorld.handleEvent(e, gamePtr->getWindow());

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
	inv.handleInput(gamePtr->getWindow());

	
}

void StatePlaying::update(sf::Time deltaTime)
{
	float dt = deltaTime.asSeconds();

	if (!hidden)
	{
		testMenu.update(dt);
	}
	spellMenuTest.update(dt);

	inv.update(dt);


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
	if (!hidden)
	{
		testMenu.render(renderer);
	}

	inv.render(renderer);

	spellMenuTest.render(renderer);

	testWorld.render(renderer);
}
