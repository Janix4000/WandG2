#pragma once

#include "Menu.h"
#include "../Characters/Hero/Hero.h"

#include "Widget.h"
#include "Icon.h"
#include "Button.h"

namespace gui
{
	class BattleHUD
	{
		void addWidget(std::unique_ptr<Widget>);

		void handleEvent(sf::Event e, const sf::RenderWindow& window);
		void render(sf::RenderTarget& renderer) const;
		void update(float dt);

	private:
		void initWidget(Widget& w);

		std::vector<std::unique_ptr<Widget>> widgets;
		sf::RectangleShape background;

		sf::Vector2f basePosition;
		sf::Vector2f baseSize;

	private:
		
		class SkillsContainer
		{
		public:
			SkillsContainer(const sf::Vector2f& position);

		private:
			std::vector<std::unique_ptr<Button>> skillsButtons;
			sf::RectangleShape background;

			sf::Vector2f basePosition;
			sf::Vector2f baseSize;

			float padding = 15.f;
			sf::Vector2f iconSize = { 64.f, 64.f };
		};
	};
	
	class SpellIconTest
		:
		public Button
	{
	public:
		SpellIconTest()
			:
			Button(ButtonSize::Icon),
			borderSize(5.f)
		{
			Button::setFunction([&]() mutable {
				isSelected = !isSelected;
				std::cout << "Hey!\n";
			});

			border.setFillColor({ 255, 0, 0, 255 });
			border.setSize(getSize());
		}

		void handleEvent(sf::Event e, const sf::RenderWindow& window) 
		{
			auto pos = sf::Mouse::getPosition(window);
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					if (!m_button.getGlobalBounds().contains(float(pos.x), float(pos.y)))
					{
						isSelected = false;
					}
				}
			}
			Button::handleEvent(e, window);
		}

		void render(sf::RenderTarget& renderer) const
		{
			if (isSelected)
			{
				renderer.draw(border);
			}
			Button::render(renderer);
		}

		void setPosition(const sf::Vector2f& pos) 
		{
			border.setPosition(pos);
			Button::setPosition(pos + sf::Vector2f{ borderSize, borderSize });
		}

		sf::Vector2f getSize() const 
		{
			return Button::getSize() + sf::Vector2f{2*borderSize, 2*borderSize};
		}

		void update(float dt) 
		{
			Button::update(dt);
		}

	private:
		bool isSelected = false;

		float borderSize;
		Rectangle border;
	};

	/*
	std::unique_ptr<SpellIconTest> make_spell_icon()
	{
		return std::make_unique<SpellIconTest>();
	}
	*/

	class SpellMenu
		:
		public Menu
	{
	public:
		SpellMenu(const sf::Vector2f& pos ,const MainHero& target)
			:
			Menu(pos, Menu::MenuOrientation::Horizontal)
		{
			Menu::padding = 5;
			setTarget(target);
		}

	private:
		const SpellVector* spells;

		void setTarget(const MainHero& target)
		{
			spells = &target.getSpells();

			for (const auto& spell : *spells)
			{
				auto skillIcon = std::make_unique<gui::SpellIconTest>();

				skillIcon->setTexture(spell.getTexture());

				/*
				auto skillButton = gui::make_button();
				skillButton->setTexture(spell.getTexture());
				skillButton->setFunction([&]() {
					std::cout << spell.getInfo().name << std::endl;
				});

				addWidget(std::move(skillButton));
				*/

				addWidget(std::move(skillIcon));
			}

		}

	};
}