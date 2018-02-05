#include "Textbox.h"


namespace gui {

TextBox::TextBox(std::string& modString)
	:  
	pModString (&modString)
{
    label.setCharacterSize(15);
    rect.setFillColor({52, 152, 219});
    rect.setSize({256, 64});
}

void TextBox::setLabel(const std::string& str)
{
    label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    handleClick     (e, window);
    handleTextInput (e);
}

void TextBox::render(sf::RenderTarget& renderer) const
{
    
    renderer.draw(rect);
    renderer.draw(label);
    renderer.draw(text);
}

void TextBox::update(float dt)
{
	if (!isActive) {
		rect.setFillColor({ 52, 152, 219 });
	}
	else {
		rect.setFillColor({ 82, 132, 239 });
	}
	holdTime += dt;
	while (holdTime > 0.7f)
	{
		isVerticalBarVisible = !isVerticalBarVisible;
		holdTime -= 0.7f;
	}
	setEnding();
}



void TextBox::setPosition(const sf::Vector2f& pos)
{
    position = pos;

    rect.setPosition(position);
    label.setPosition(position.x, position.y + label.getGlobalBounds().height - rect.getGlobalBounds().height / 2);
    text.setPosition  (position);
    text.move(padding, rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const
{
    return  {rect.getSize().x,
             rect.getSize().y + label.getGlobalBounds().height};
}

void TextBox::handleClick (sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    if (rect.getGlobalBounds().contains(float(pos.x), float(pos.y)))
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                isActive = true;
            }
        }
    }
    else
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                isActive = false;
            }
        }
    }
}

void TextBox::handleTextInput (sf::Event e)
{

    if (e.type == sf::Event::TextEntered && isActive)
    {
        //Get the key that was entered
        unsigned char keyCode = e.text.unicode;

        //Test if it within the "Type-able keys eg aA to zZ and 0 to 9
        if (isValidCharacter(keyCode))
        {
			if (text.getGlobalBounds().width + 2 * padding + text.getCharacterSize() < rect.getGlobalBounds().width)
			{
				pModString->push_back(keyCode);
			}
        }
        else if (isBackspace(keyCode))
        {
            //prevents popping back an empty string
            if (pModString->length() > 0)
                pModString->pop_back();
        }

		else if (isEnter(keyCode))
		{
			pModString->push_back('\n');
		}
        text.setString(*pModString );
    }
}

void TextBox::setEnding()
{
	if (!isActive)
	{
		text.setString(*pModString);
	}
	else
	{
		if (isVerticalBarVisible != hasEnding)
		{
			hasEnding = !hasEnding;
			if (hasEnding)
			{
				text.setString(*pModString + "|");
			}
			else
			{
				text.setString(*pModString);
			}
		}
	}
}

 //return true if the character is within the valid keys eg aA to zZ and 0 to 9
bool TextBox::isValidCharacter(unsigned char keyCode)
{
    return  keyCode >= 32 &&
            keyCode <= 127;
}

bool TextBox::isBackspace(unsigned char keycode)
{
    return keycode == 8;
}

bool TextBox::isEnter(unsigned char keycode)
{
	return keycode == 17;
}


}
