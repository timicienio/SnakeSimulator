#include "State.h"

State::State(std::stack<State*>* states, sf::RenderWindow* window)
	:states(states),
	 window(window)
{
}
