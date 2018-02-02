#pragma once

#include "Widget.h"
namespace gui
{
	class Icon
		:
		public gui::Widget
	{
	public:
		Icon(const float& value, const float& maxValue);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;

		void render(sf::RenderTarget& renderer) override;

		void setPosition(const sf::Vector2f& pos) override;

		sf::Vector2f getSize() const override;

		void update(float dt) override;


		void setColor(sf::Color c);
		void setMaxRadius(float r);
		void setTexture(TexturePtr tex);
		void setTextureInside(TexturePtr tex);
		void setTextureBackground(TexturePtr tex);




	private:
		Circle backgroundCircle;
		Circle insideCircle;

		sf::Vector2f position;

		const float* value;
		const float* maxValue;

		float maxRadius;
		sf::Color colorDifference;
		sf::Uint8 cDiff = 32;

	private:
		void calcInsideCircle();
		float getInsideRadius() const;
	};

	std::unique_ptr<Icon> inline make_icon(const float& value, const float& maxValue)
	{
		return std::make_unique<Icon>(value, maxValue);
	}

}