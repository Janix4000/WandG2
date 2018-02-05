#include "StackMenu.h"

#include "../ResourceManager/ResourceHolder.h"

constexpr int BASEY = 25;

namespace gui
{

StackMenu::StackMenu(const sf::RenderWindow& window)
	:
	basePosition(float(window.getSize().x / 2), BASEY),
	baseSize(300.f, 20.f)
{
    background.setFillColor( {100, 100, 100, 128} );
    background.setSize(baseSize);
    background.setPosition(basePosition.x - baseSize.x / 2, BASEY - 30);
}

StackMenu::StackMenu(const sf::Vector2f& position)
	:
	basePosition(position),
	baseSize(300.f, float(padding))
{
    background.setFillColor({100, 100, 100, 128});
    background.setSize(baseSize);
    background.setPosition(position);
}

StackMenu::StackMenu(StackMenu&& other)
	:
	widgets(std::move(other.widgets)),
	background(std::move(other.background)),
	basePosition(other.basePosition),
	baseSize(other.baseSize)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    widgets = std::move(other.widgets);
    background = std::move(other.background);
    basePosition = other.basePosition;
    baseSize = other.baseSize;

    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    widgets.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    widget.setPosition({basePosition.x - widget.getSize().x / 2,
                       basePosition.y});


    basePosition.y += widget.getSize().y + padding;
    baseSize.y += widget.getSize().y + padding;
    background.setSize(baseSize);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : widgets) {
        widget->handleEvent(e, window);
    }
}

void StackMenu::render(sf::RenderTarget& renderer) const
{
    renderer.draw(background);
    for (auto& widget : widgets) {
        widget->render(renderer);
    }
}

void StackMenu::update(float dt)
{
	for (auto& widget : widgets) {
		widget->update(dt);
	}
}

}
