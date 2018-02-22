#pragma once

#include "Slot.h"

class Inventory
{
private:


public:
	

private:

public:
	Inventory(sf::Vector2i capacity = {2, 1})
		:
		capacity(capacity)
	{
		slots.reserve(capacity.x * capacity.y);
		for (int i = 0; i < capacity.x * capacity.y; i++)
		{
			slots.emplace_back(Slot({ 0.f, 0.f }));
		}
		setPosition({ 100.f, 0.f });
	}

	bool hasFreeSlot() const
	{
		return std::any_of(slots.begin(), slots.end(), [](const auto& item) {
			return item.isFree();
		});
	}

	void addItem(ItemPtr item)
	{
		auto freeSlot = std::find_if(slots.begin(), slots.end(), [](const auto& item) {
			return item.isFree();
		});

		assert(freeSlot != slots.end());

		freeSlot->applyItem(std::move(item));
	}

	void render(sf::RenderTarget& renderer) const
	{
		for (auto& slot : slots)
		{
			slot.render(renderer);
		}

		for (auto& slot : slots)
		{
			if(!slot.isHold())
				slot.drawItem(renderer);
		}

		for (auto& slot : slots)
		{
			if (slot.isHold())
				slot.drawItem(renderer);
		}

	}

	void update(float dt)
	{
		for (auto& slot : slots)
		{
			slot.update(dt);
		}
	}

	void handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		for (auto& slot : slots)
		{
			slot.handleEvent(e, window);
		}
	}

	void handleInput(const sf::RenderWindow& window)
	{
		for (auto& slot : slots)
		{
			slot.handleInput(window);
		}

		handleItemSwapping(window);
	}

	ItemPtr getItem(int index)
	{
		assert(index < slots.size());
		assert(!slots[index].isFree());

		return slots[index].getItem();
	}

	void setPosition(sf::Vector2f position)
	{
		pos = position;
		sf::Vector2f slotSize(64 + 16, 64 + 16);

		for (int y = 0; y < capacity.y; y++)
		{
			for (int x = 0; x < capacity.x; x++)
			{
				slots[x + y * capacity.x].setPosition( { float(slotSize.x * x + pos.x ), float(slotSize.y * y + pos.y) } );
			}
		}
	}

private:

	void handleItemSwapping(const sf::RenderWindow& window)
	{
		auto droppedItem = std::find_if(slots.begin(), slots.end(), [](const auto& slot) {
			return slot.isDropped();
		});

		if (droppedItem != slots.end())
		{
			auto targetToSwap = std::find_if(slots.begin(), slots.end(), [&](const auto& slot) {
				return droppedItem->isTargeting(slot, window);
			});
			
			if (targetToSwap == droppedItem)
			{
				targetToSwap = std::find_if(targetToSwap + 1, slots.end(), [&](const auto& slot) {
					return droppedItem->isTargeting(slot, window);
				});
			}

			if (droppedItem != targetToSwap && targetToSwap != slots.end())
			{
				droppedItem->replaceItems( *targetToSwap);
			}
			else
			{
				droppedItem->normItem();
			}
		}
	}
	
private:
	sf::Vector2f pos;

	sf::Vector2i capacity;

	std::vector<Slot> slots;
};
