#pragma once

#include <SFML/System/Vector2.hpp>
#include "../Utility/Vec2.h"

class FreePhysic
{
public:
	void update(float dt)
	{
		vel += acc * dt;
		pos += vel * dt;
		acc *= 0.f;
	}

	Vec2 acc;
	Vec2 vel;
	Vec2 pos;
};