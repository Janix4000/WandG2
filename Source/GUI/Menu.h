#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Widget.h"


namespace gui
{
	class Menu
		:
		public sf::NonCopyable
	{
	public:
		enum class MenuOrientation
		{
			Vertical,
			Horizontal
		} menuOrient;

	public:
		Menu(const sf::RenderWindow& window, MenuOrientation orient = MenuOrientation::Vertical);
		Menu(const sf::Vector2f& position, MenuOrientation orient = MenuOrientation::Vertical);

		Menu(Menu&& other);
		Menu& operator =(Menu&& other);


		~Menu() = default;
		void addWidget(std::unique_ptr<Widget> w);

		void handleEvent(sf::Event e, const sf::RenderWindow& window);
		void render(sf::RenderTarget& renderer);
		void update(float dt);

	protected:
		float padding = 25;
	private:
		void initWidget(Widget& w);

		void calcBackground();

		std::vector<std::unique_ptr<Widget>> widgets;
		sf::RectangleShape background;
		
		sf::Vector2f position;
		sf::Vector2f basePosition;
		sf::Vector2f baseSize;

	};
}