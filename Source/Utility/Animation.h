#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Animation
{
public:
	Animation(sf::Texture sourceTexture, sf::Rect<int> framesBegin, int numberOfFrames, float timeOfFrame);
	Animation() = default;
	
	void update(float dt);
	void draw(sf::RenderTarget& rt) const;
	void applyToSprite(sf::Sprite& target) const;
private:
	void incrementIndex();

private:
	float frameTime;
	int curentFrameIndex;
	std::vector<sf::Rect<int>> frames;
	float time = 0.f;
	sf::Texture source;

};