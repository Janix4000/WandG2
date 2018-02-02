#pragma once
#include "../Utility/Vec2.h"
#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile(const Vec2& pos, const Vec2& moveDir, int dmg = 10, float lifeTime = 5.f);

private:
	float timeToDie;
	int damage;
	sf::Sprite sprite;

	Vec2 pos;
	Vec2 moveDirection;
	float speed;

public:

	void update(float dt);
	void draw(sf::RenderTarget& rt) const;

	sf::FloatRect getHitbox() const;

	void kill();
	bool isReadyToDie() const;

private:
	Vec2 getVelocity() const;

};