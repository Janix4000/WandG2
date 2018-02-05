#include "Icon.h"

namespace gui
{
	Icon::Icon(const float & value, const float & maxValue)
		:
		Widget(),
		value(&value),
		maxValue(&maxValue),
		cDiff(64u)
	{
		colorDifference = { cDiff, cDiff, cDiff, 0 };

		setMaxRadius(64);
		setColor({ 52, 152, 219 });

		backgroundCircle.setOutlineThickness(5);
		backgroundCircle.setOutlineColor(sf::Color::Black);
	}

	void Icon::handleEvent(sf::Event e, const sf::RenderWindow & window)
	{
	}

	void Icon::render(sf::RenderTarget & renderer) const
	{
		renderer.draw(backgroundCircle);
		renderer.draw(insideCircle);

	}

	void Icon::setPosition(const sf::Vector2f & pos)
	{
		position = pos;
		insideCircle.setPosition(pos);
		backgroundCircle.setPosition(pos);
	}

	sf::Vector2f Icon::getSize() const
	{
		return { 2*maxRadius, 2*maxRadius };
	}

	void Icon::update(float dt)
	{
		calcInsideCircle();
	}

	void Icon::setColor(sf::Color c)
	{
		insideCircle.setFillColor(c);
		sf::Color bgc = c - colorDifference;
		backgroundCircle.setFillColor(bgc);
	}

	void Icon::setMaxRadius(float r)
	{
		maxRadius = r;
		backgroundCircle.setRadius(r);
	}

	void Icon::setTexture(TexturePtr tex)
	{
		setTextureInside(tex);
		setTextureBackground(tex);
	}

	void Icon::setTextureInside(TexturePtr tex)
	{
		insideCircle.setTexture(tex);
	}

	void Icon::setTextureBackground(TexturePtr tex)
	{
		backgroundCircle.setTexture(tex);
	}

	void Icon::calcInsideCircle()
	{
		const float inR = getInsideRadius();
		insideCircle.setRadius(inR);
		insideCircle.setPosition(position);

		insideCircle.setOrigin(inR - maxRadius, inR - maxRadius);
	}

	float Icon::getInsideRadius() const
	{
		return (*value / *maxValue) * maxRadius;
	}

}