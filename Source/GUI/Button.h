#ifndef GUIBUTTON_H_INCLUDED
#define GUIBUTTON_H_INCLUDED

#include <functional>

#include "Widget.h"

namespace gui
{
    enum class ButtonSize
    {
        Small,
        Wide,
		Icon
    };

    class Button : public Widget
    {
        public:
            Button(ButtonSize s = ButtonSize::Wide);

			//~Button() = default;

            void setFunction (std::function<void(void)> func);
            void setText (const std::string& str);
            void setTexture (TexturePtr tex);

            void handleEvent(sf::Event e, const sf::RenderWindow& window) override;

            void render(sf::RenderTarget& renderer) override;

            void setPosition(const sf::Vector2f& pos) override;

            sf::Vector2f getSize() const override;

			void update(float dt) override;

        private:
            void updateText();

            sf::Vector2f    m_position;

	protected:
            Rectangle   m_button;
	private:
            Text        m_text;
            std::function<void(void)> m_function = [](){};

    };

	std::unique_ptr<Button> inline make_button()
	{
		return std::make_unique<Button>();
	}
}


#endif // GUIBUTTON_H_INCLUDED
