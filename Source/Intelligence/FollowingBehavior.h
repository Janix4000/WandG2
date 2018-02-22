#pragma once

#include "../Objects/FreePhysic.h"
class FollowingBehavior
{
public:
	void applyTo(FreePhysic& objPhysic)
	{
		if (hasTarget)
		{
			applyForceTo(objPhysic);
		}
		else
		{
			stopObj(objPhysic);
		}
	}

	void setTarget(const sf::Vector2f& newTarget)
	{
		target = { newTarget.x, newTarget.y };
		hasTarget = true;
	}

private:

	bool hasTarget = false;
	Vec2 target;

	float maxSpeed = 50.f;
	float maxAcc = 10.f;

	float retardationDist = 100.f;

	void stopObj(FreePhysic& objPhysic)
	{
		objPhysic.vel *= 0.f;
		objPhysic.acc *= 0.f;
	}

	void applyForceTo(FreePhysic& objPhysic)
	{
		const auto pos = objPhysic.pos;

		auto desire = target - pos;

		setDesireMag(desire);

		auto force = makeForce(desire, objPhysic);

		objPhysic.acc += force;
	}

	void setDesireMag(Vec2& desire)
	{
		const float distSqr = desire.getLenSq();

		float mag = maxSpeed;
		if (distSqr < retardationDist*retardationDist)
		{
			float dist = sqrt(distSqr);
			mag = map(dist, 0.f, retardationDist, 0.f, maxSpeed);
		}

		desire.setLen(mag);
	}

	Vec2 makeForce(const Vec2& desire, const FreePhysic& objPhysic)
	{
		const auto vel = objPhysic.vel;
		auto force =  desire - vel;
		force.limit(maxAcc);
		return force;
	}

};