#include "Animation.h"

Animation::Animation(sf::Texture sourceTexture, sf::IntRect framesBegin, int numberOfFrames, float timeOfFrame)
	:
	frameTime(timeOfFrame),
	source(sourceTexture)
{
	curentFrameIndex = 0;

	int frameL = framesBegin.left;
	int frameT = framesBegin.top;
	int frameW = framesBegin.width;
	int frameH = framesBegin.height;

	auto sourceSize = source.getSize();
	frames.resize(numberOfFrames);
	int yOffset = 0;

	for (int i = 0; i < numberOfFrames; i++)
	{
		sf::IntRect frame;

		int x = frameL + i * frameW;
		
		if (x + frameW > sourceSize.x)
		{
			x = 0;
			yOffset += frameH;
		}
		
		int y = frameT + yOffset;
		

		frame.top = y;
		frame.left = x;
		frame.width = frameW;
		frame.height = frameH;

		frames[i] = frame;
	}
}

void Animation::update(float dt)
{
	time += dt;
	while (time > frameTime)
	{
		time -= frameTime;
		incrementIndex();
	}
}

void Animation::applyToSprite(sf::Sprite & target) const
{
	target.setTexture(source);
	target.setTextureRect(frames[curentFrameIndex]);
}

void Animation::incrementIndex()
{
	if (++curentFrameIndex >= frames.size())
	{
		curentFrameIndex = 0;
	}
}
