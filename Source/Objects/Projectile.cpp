#include "Projectile.h"

Projectile::Projectile(const Vec2& pos, const Vec2 & moveDir, int dmg, float lifeTime)
	:
	damage(dmg),
	timeToDie(lifeTime),
	pos(pos)
{
	moveDirection = moveDir.getNormalized();
	speed = 10;
}

void Projectile::update(float dt)
{
	timeToDie -= dt;

	pos += getVelocity() * dt;
	sprite.setPosition(pos);
}

void Projectile::draw(sf::RenderTarget & rt) const
{
	rt.draw(sprite);
}

sf::FloatRect Projectile::getHitbox() const
{
	return sprite.getGlobalBounds();
}

void Projectile::kill()
{
	timeToDie = 0.f;
}

bool Projectile::isReadyToDie() const
{
	return timeToDie <= 0.f;
}

Vec2 Projectile::getVelocity() const
{
	return moveDirection * speed;
}
