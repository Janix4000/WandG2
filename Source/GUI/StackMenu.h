#ifndef STACKMENU_H_INCLUDED
#define STACKMENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Widget.h"
#include <SFML/System/NonCopyable.hpp>

namespace gui
{

class StackMenu 
	: 
	public sf::NonCopyable
{
    public:
        StackMenu(const sf::RenderWindow& window);
        StackMenu(const sf::Vector2f& position);

        StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);


        ~StackMenu() = default;
        void addWidget(std::unique_ptr<Widget>);

        void handleEvent(sf::Event e, const sf::RenderWindow& window);
        void render(sf::RenderTarget& renderer)const;
		void update(float dt);

    private:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> widgets;
        sf::RectangleShape background;

        sf::Vector2f basePosition;
        sf::Vector2f baseSize;

		int padding = 20;
};

}

#endif // STACKMENU_H_INCLUDED
