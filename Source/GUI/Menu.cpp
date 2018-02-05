#include "Menu.h"

#include "../ResourceManager/ResourceHolder.h"

constexpr int BASEY = 25;
namespace gui
{

	Menu::Menu(const sf::RenderWindow & window, MenuOrientation orient)
		:
		Menu({ float(window.getSize().x / 2), 20.f }, orient)
	{
	}

	Menu::Menu(const sf::Vector2f & position, MenuOrientation orient)
		:
		menuOrient(orient),
		position(position),
		basePosition(position + sf::Vector2f{padding, padding}),
		baseSize(padding, padding)
	{
		background.setFillColor({ 100, 100, 100, 128 });
		background.setSize(baseSize);
		background.setPosition(position);
	}

	Menu::Menu(Menu && other)
		:
		widgets(std::move(other.widgets)),
		background(std::move(other.background)),
		position(other.position),
		basePosition(other.basePosition),
		baseSize(other.baseSize),
		menuOrient(other.menuOrient)
	{
	}
	Menu & Menu::operator=(Menu && other)
	{
		widgets = std::move(other.widgets);
		background = std::move(other.background);
		position = other.position;
		basePosition = other.basePosition;
		baseSize = other.baseSize;
		menuOrient = other.menuOrient;

		return *this;
	}
	void Menu::addWidget(std::unique_ptr<Widget> w)
	{
		initWidget(*w);
		widgets.push_back(std::move(w));
	}

	void Menu::handleEvent(sf::Event e, const sf::RenderWindow & window)
	{
		for (auto& widget : widgets)
		{
			widget->handleEvent(e, window);
		}
	}

	void Menu::render(sf::RenderTarget & renderer) const
	{
		renderer.draw(background);
		for (auto& widget : widgets)
		{
			widget->render(renderer);
		}
	}

	void Menu::update(float dt)
	{
		for (auto& widget : widgets)
		{
			widget->update(dt);
		}
	}

	void Menu::initWidget(Widget & w)
	{

		if (menuOrient == MenuOrientation::Vertical)
		{
			baseSize.x = std::max(baseSize.x, w.getSize().x + 2 * padding);

			w.setPosition({ basePosition.x - w.getSize().x / 2, basePosition.y });
			basePosition.y += w.getSize().y + padding;
			baseSize.y += w.getSize().y + padding;
		}
		else
		{
			baseSize.y = std::max(baseSize.y, w.getSize().y + 2 * padding);

			w.setPosition({ basePosition.x , basePosition.y - w.getSize().y / 2 });
			basePosition.x += w.getSize().x + padding;
			baseSize.x += w.getSize().x + padding;
		}
		calcBackground();
	}
	void Menu::calcBackground()
	{
		background.setSize(baseSize);
		if (menuOrient == MenuOrientation::Vertical)
			background.setPosition(basePosition.x - baseSize.x / 2, position.y);
		else
			background.setPosition(position.x, basePosition.y - baseSize.y / 2);
	}
}