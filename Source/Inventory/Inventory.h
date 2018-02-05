#pragma once
#include <vector>
#include <memory>

#include "Items\Item.h"
#include "../GUI/Widget.h"

using ItemPtr = std::unique_ptr<Item>;

class Inventory
{
private:


public:
	class ItemObj
		: public gui::Widget
	{
	public:
		ItemObj(const sf::Vector2f& position)
		{
			setPosition(position);
		}

		void applyItem(ItemPtr i)
		{
			item = std::move(i);
			itemSprite.setTexture(*item->getTexture());
			hasItem = true;
			background.setSize((sf::Vector2f)item->getTexture()->getSize());
		}

		void setPosition(const sf::Vector2f& position) override
		{
			pos = position;
			background.setPosition(pos);
			itemSprite.setPosition(pos);
		}

		sf::Vector2f getSize() const override
		{
			return background.getSize();
		}

		void update(float dt) override
		{
			
		}

		void handleInput(const sf::RenderWindow& window)
		{
			if (isHold)
			{
				setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) + shiftPos);

			}
		}

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override
		{
			
			if (background.isClicked(e, window))
			{
				isHold = true;
				shiftPos = pos - sf::Vector2f(sf::Mouse::getPosition(window));
			}

			switch (e.type)
			{
			case sf::Event::MouseButtonReleased:
				isHold = false;
			default:
				break;
			}
		}

		void render(sf::RenderTarget& renderer) const override
		{
			if (hasItem)
			{
				renderer.draw(itemSprite);
			}
		}

	private:
		ItemPtr item;
		sf::Vector2f pos;
		Rectangle background;
		sf::Sprite itemSprite;

		sf::Vector2f shiftPos;

		bool isHold = false;
		bool hasItem = false;
	};




public:
	void addItem(ItemPtr item)
	{

	}


private:
	std::vector < ItemPtr > items;
};