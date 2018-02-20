#pragma once

#include "StateBase.h"

class StateTest
	: public StateBase
{
public:
	StateTest(Game& game);

	void handleEvent(sf::Event e) override;

	void handleInput() override;

	void update(sf::Time deltaTime) override;

	void fixedUpdate(sf::Time deltaTime) override;

	void render(sf::RenderTarget& renderer) const override;



};
