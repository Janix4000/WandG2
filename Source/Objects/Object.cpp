#include "Object.h"

Object::Object()
	:
	pos(0.f, 0.f),
	vel(0.f, 0.f),
	acc(0.f, 0.f)
{
	shape.setRadius(30);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(5);
}

void Object::update(float dt)
{
	vel += acc * dt;
	pos += vel * dt;
	acc *= 0.f;

	shape.setPosition(pos);
}

void Object::draw(sf::RenderTarget & rt) const
{
	rt.draw(shape);
}

void Object::attract(Vec2 target)
{
	Vec2 attract;
	attract = target - pos;
	float strength;
	strength = 10000.f / attract.getLenSq();
	attract.setLen(strength);
	acc += attract;
}


