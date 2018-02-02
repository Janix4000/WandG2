#pragma once
#include <SFML/Graphics.hpp>
#include "../Utility/Vec2.h"

class Object
{
public:
	Object();

public:
	void update(float dt);
	void draw(sf::RenderTarget& rt) const;
	void handleInput(const sf::Event& e);

	void attract(Vec2 target);

private:
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;

	sf::CircleShape shape;

private:
};
