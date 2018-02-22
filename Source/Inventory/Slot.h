#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include "Items\Item.h"
#include "../GUI/Widget.h"

class Slot
	: public gui::Widget
{
private:
	enum class State
	{
		NoItem,
		Normal,
		Hold,
		Dropped
	} status = State::NoItem;

public:
	Slot(const sf::Vector2f& position)
		:
		borderSize(4.f, 4.f)
	{
		setPosition(position);
		background.setTexture(ResourceHolder::get().textures.acquire("item_back"));
		border.setFillColor({ 64, 32,0 });

		sf::Vector2f size = { 64, 64 };
		background.setSize(size);
		border.setSize(size + 2.f * borderSize);
	}

	void applyItem(ItemPtr i)
	{
		assert(status == State::NoItem);

		item = std::move(i);

		status = State::Normal;

		const auto size = (sf::Vector2f)item->getTexture()->getSize();
		background.setSize(size);
		border.setSize(size + 2.f * borderSize);

		normItem();
	}

	ItemPtr getItem()
	{
		assert(status != State::NoItem);
		status = State::NoItem;

		return std::move(item);
	}

	void replaceItems(Slot& other)
	{
		ItemPtr firstItem, secondItem;
		bool hasFirst = false, hasSecond = false;

		if (status != State::NoItem)
		{
			firstItem = getItem();
			hasFirst = true;
		}

		if (other.status != State::NoItem)
		{
			secondItem = other.getItem();
			hasSecond = true;
		}

		if (hasFirst)
		{
			other.applyItem(std::move(firstItem));
		}
		if (hasSecond)
		{
			applyItem(std::move(secondItem));
		}
	}

	void setPosition(const sf::Vector2f& position) override
	{
		pos = position;

		border.setPosition(pos);
		background.setPosition(pos + borderSize);

		if (status != State::NoItem)
			item->setPosition(pos + borderSize);
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
		if (status == State::Hold)
		{
			moveSpriteToMouse(window);
		}

	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window) override
	{

		if (background.isClicked(e, window))
		{
			if (status == State::Normal)
			{
				status = State::Hold;
				shiftPos = pos - sf::Vector2f(sf::Mouse::getPosition(window));
			}
		}

		switch (e.type)
		{
		case sf::Event::MouseButtonReleased:

			if (status == State::Hold)
			{
				status = State::Dropped;
			}
			break;
		default:
			break;
		}
	}

	void render(sf::RenderTarget& renderer) const override
	{
		renderer.draw(border);
		renderer.draw(background);
	}

	void drawItem(sf::RenderTarget& renderer) const
	{
		if (status != State::NoItem && status != State::Dropped)
		{
			item->draw(renderer);
		}
	}

	bool isDropped() const
	{
		return status == State::Dropped;
	}

	void normItem()
	{
		status = State::Normal;
		moveSpriteToBackground();
	}

	bool isTargeting(const Slot& another, const sf::RenderWindow& window) const
	{
		return another.background.isRolledOn(window);
	}

	bool isFree() const
	{
		return status == State::NoItem;
	}

	bool isHold() const
	{
		return status == State::Hold;
	}

private:
	void moveSpriteToMouse(const sf::RenderWindow& window)
	{
		item->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) + shiftPos);
	}

	void moveSpriteToBackground()
	{
		item->setPosition(background.getPosition());
	}

private:
	sf::Vector2f borderSize;

	ItemPtr item;
	sf::Vector2f pos;
	Rectangle background;
	Rectangle border;

	sf::Vector2f shiftPos;
};