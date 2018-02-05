#ifndef STATEBASE_H_INCLUDED
#define STATEBASE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

class Game;

class StateBase 
	:
	public sf::NonCopyable
{
    public:
        StateBase(Game& game)
        :   gamePtr   (&game)
        {}

        virtual ~StateBase() = default;

        virtual void handleEvent(sf::Event e) = 0;

        virtual void handleInput() = 0;

        virtual void update(sf::Time deltaTime) = 0;

        virtual void fixedUpdate(sf::Time deltaTime) = 0;

        virtual void render(sf::RenderTarget& renderer) const = 0;

    protected:
        Game* gamePtr;
};

#endif // STATEBASE_H_INCLUDED
