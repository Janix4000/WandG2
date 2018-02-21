#pragma once

#include "Floor.h"
#include "../Objects/Entity.h"

class Perspective
{
public:
	Perspective(const Floor& baseFloor)
		:
		floorPtr(&baseFloor)
	{}

	void applyPerspective(Entity& entity)
	{

	}


private:
	const Floor* floorPtr = nullptr;


};