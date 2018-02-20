#pragma once

#include "Widget.h"

namespace gui
{

	class ScrollBar
		:
		public Widget
	{


	public:
		void handleEvent(sf::Event e, const sf::RenderWindow& window) override
		{}

		void render(sf::RenderTarget& renderer) const override
		{}

		void setPosition(const sf::Vector2f& pos)override
		{}

		sf::Vector2f getSize() const override
		{}

		void update(float dt) override
		{}
	};

}