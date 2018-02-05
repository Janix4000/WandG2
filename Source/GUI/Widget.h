#ifndef GUIWIDGET_H_INCLUDED
#define GUIWIDGET_H_INCLUDED

#include <memory>

#include <SFML/Graphics.hpp>
#include "../ResourceManager/ResourceHolder.h"

namespace gui
{
    class Widget
    {
        public:
            virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

            virtual void render(sf::RenderTarget& renderer) const = 0;

            virtual void setPosition(const sf::Vector2f& pos) = 0;

            virtual sf::Vector2f getSize() const = 0;

			virtual void update(float dt) = 0;

			//virtual ~Widget() = 0;

        protected:
            class Text : public sf::Text
            {
            public:
				Text();
				void setFont(FontPtr font)
				{
					this->font = font;
					sf::Text::setFont(*this->font);
				}
			private:
				FontPtr font;
            };

            class Rectangle : public sf::RectangleShape
            {
                public:
                    bool isRolledOn (const sf::RenderWindow& window) const;
                    bool isClicked  (sf::Event, const sf::RenderWindow& window);
					bool hasTexture() const;
					void setTexture(TexturePtr texture)
					{
						this->texture = texture;
						RectangleShape::setTexture(this->texture.get());
					}
			private:
				TexturePtr texture;
            };

			class Circle
				:
				public sf::CircleShape
			{
			public:
				bool hasTexture() const;
				void setTexture(TexturePtr texture)
				{
					this->texture = texture;
					CircleShape::setTexture(this->texture.get());
				}
			private:
				TexturePtr texture;
			};
    };
}

#endif // GUIWIDGET_H_INCLUDED
