#pragma once

#include "../Objects/FreePhysic.h"
class FollowingBehavior
{
public:

	FollowingBehavior()
	{
		maxSpeed = 300.f;
		maxAcc = maxSpeed;

		retardationDist = 400.f;
		catchDist = 30.f;

		holdTime = timeToArrive;
	}


	void applyTo(float dt, FreePhysic& objPhysic)
	{
		if (hasTarget)
		{
			if(holdTime > 0.f)
				goTo(dt, objPhysic);
			else
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
		if (!hasTarget)
		{
			holdTime = timeToArrive;
			hasTarget = true;
		}
	}

	void stop(FreePhysic& objPhysic)
	{
		stopObj(objPhysic);
		hasTarget = false;
	}


private:

	bool hasTarget = false;
	Vec2 target;

	float maxSpeed = 200.f;
	float maxAcc = 2.f * maxSpeed;

	float retardationDist = 500.f;
	float catchDist;

	void stopObj(FreePhysic& objPhysic)
	{
		objPhysic.vel *= 0.f;
		objPhysic.acc *= 0.f;
	}

	void applyForceTo(FreePhysic& objPhysic)
	{
		const auto pos = objPhysic.pos;

		auto distVec = target - pos;

		auto desire = makeDesire(distVec);

		auto force = makeForce(desire, objPhysic);

		objPhysic.acc += force;

		objPhysic.vel.limit(maxSpeed);

		handleCatching(objPhysic);
	}

	Vec2 makeDesire(Vec2& distVec)
	{
		const float distSqr = distVec.getLenSq();

		float mag = maxSpeed;
		if (isInRadius(distSqr, retardationDist))
		{
			float dist = sqrt(distSqr);
			mag = map(dist, 0.f, retardationDist, 0.f, maxSpeed);
		}

		Vec2 desire = distVec;

		desire.setLen(mag);
		return desire;
	}

	bool isInRadius(Vec2 distVec, float radius)
	{
		float distSqr = distVec.getLenSq();
		return isInRadius(distSqr, radius);
	}
	bool isInRadius(float distSqr, float radius)
	{
		return distSqr < pow(radius, 2);
	}

	Vec2 makeForce(const Vec2& desire, const FreePhysic& objPhysic)
	{
		const auto vel = objPhysic.vel;
		auto force = desire - vel;
		force.limit(maxAcc);
		return force;
	}

	void handleCatching(FreePhysic& objPhysic)
	{
		Vec2 distVec = objPhysic.pos - target;

		const float distSqr = distVec.getLenSq();

		if (!isInRadius(distSqr, catchDist))
		{
			auto maxDistVec = distVec;
			maxDistVec.setLen(catchDist);

			auto newPos = (target + maxDistVec);

			objPhysic.pos = newPos;
		}

		if (distSqr < 1.f)
		{
			objPhysic.vel *= 0.f;
		}
	}

	float getDistSqToTarget(const FreePhysic& objPhysic) const
	{
		auto distVec = objPhysic.pos - target;
		return distVec.getLenSq();
	}

	float getDistToTarget(const FreePhysic& objPhysic) const
	{
		return sqrt(getDistSqToTarget(objPhysic));
	}


	const float timeToArrive = 0.5f;
	float holdTime = timeToArrive;

	void goTo(float dt, FreePhysic& objPhysic)
	{
		const float dist = getDistToTarget(objPhysic);

		float d = (dt / holdTime) * dist;
		holdTime -= dt;

		auto newVel = target - objPhysic.pos;

		newVel.setLen(d);
		objPhysic.pos += newVel;
		objPhysic.vel *= 0.f;
		objPhysic.acc *= 0.f;
	}

};