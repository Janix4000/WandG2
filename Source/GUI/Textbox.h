#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <functional>

#include "Widget.h"

namespace gui
{
    class TextBox : public gui::Widget
    {
        public:
            TextBox(std::string& modString);

            void setLabel       (const std::string& str);
            void setTexture     (const sf::Texture& tex);

            void handleEvent    (sf::Event e, const sf::RenderWindow& window) override;
            void render         (sf::RenderTarget& renderer) const    override;
			void update(float dt) override;
            void setPosition    (const sf::Vector2f& pos)       override;
            sf::Vector2f getSize() const                        override;


        private:
            void handleClick    (sf::Event e, const sf::RenderWindow& window);
            void handleTextInput(sf::Event e);
			void setEnding();

            bool isValidCharacter   (unsigned char keyCode);
            bool isBackspace        (unsigned char keycode);
			bool isEnter(unsigned char keycode);

            sf::Vector2f    position;
			int padding = 5;

            Rectangle       rect;
            Text            text;
            Text            label;
            std::string*    pModString;

            bool isActive = false;
			bool isVerticalBarVisible = false;
			bool hasEnding = false;
			float holdTime = 0.f;

    };
}

#endif // TEXTBOX_H_INCLUDED
