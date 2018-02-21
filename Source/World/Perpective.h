#pragma once

#include <cassert>

#include "Floor.h"
#include "../Objects/Entity.h"

class Perspective
{
public:
	Perspective(Floor& baseFloor, float perspectiveFactor)
		:
		floorPtr(&baseFloor),
		perspectiveFactor(perspectiveFactor)
	{}

	Perspective(Floor& baseFloor, sf::Vector2f absoluteSize)
		:
		floorPtr(&baseFloor) 
	{
		perspectiveFactor = getPerspectiveFactorByRealFloorHeight(absoluteSize.y);
	}

	void applyPerspective(Entity& entity)
	{
		auto& sprite = entity.getSprite();

		const auto pos = entity.getPosition();
		const float yFactor = getYFactor(pos);

		const auto perspectivePosition = getPerspectivePosition(pos, yFactor);

		sprite.setPosition(perspectivePosition);
		sprite.setScale(yFactor, yFactor);
	}

	void applyPerspectiveToFloor()
	{
		const float yFactor = getYFactor(-(floorPtr->getSize()));
		floorPtr->getShape().setScale(1.f, yFactor);
	}

	void removePerspective(Entity& entity)
	{
		auto& sprite = entity.getSprite();

		sprite.setScale(1.f, 1.f);
	}

	void removePerspectiveFromFloor()
	{
		auto& shape = floorPtr->getShape();

		shape.setScale(1.f, 1.f);
	}


	float getPerspectiveFactor() const
	{
		return perspectiveFactor;
	}

	void setPerspectiveFactor(float newPerspectiveFactor)
	{
		assert(newPerspectiveFactor > 0.f);
		perspectiveFactor = newPerspectiveFactor;
	}

	void setPerspectiveFloorHeight(float height)
	{
		float newPerspectiveFactor = getPerspectiveFactorByRealFloorHeight(height);
		setPerspectiveFactor(newPerspectiveFactor);
	}


private:
	Floor* floorPtr = nullptr;

	float perspectiveFactor;

	float getPerspectiveFactorByRealFloorHeight(float realFloorHeight)
	{
		const float floorHeight = floorPtr->getSize().y;
		assert(realFloorHeight < floorHeight);

		return -(realFloorHeight * floorHeight) / (realFloorHeight - floorHeight);
	}

	float getYFactor(const sf::Vector2f& pos) const
	{
		return perspectiveFactor / (perspectiveFactor - pos.y);
	}

	sf::Vector2f getPerspectivePosition(const sf::Vector2f& pos) const
	{
		const auto yFactor = getYFactor(pos);

		return getPerspectivePosition(pos, yFactor);
	}

	sf::Vector2f getPerspectivePosition(const sf::Vector2f& pos, float yFactor) const
	{
		return floorPtr->getPosition() + sf::Vector2f(pos.x, pos.y * yFactor);
	}
};