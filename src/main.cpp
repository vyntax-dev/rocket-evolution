#include <SFML/Graphics.hpp>
#include "events.h"
#include "config.h"

using namespace sf;

int main()
{
	RenderWindow window( VideoMode( conf::windowSize ), "SFML works!", Style::None );
	window.setFramerateLimit(conf::framerate);

	while ( window.isOpen() )
	{
		processEvents( window);

		window.clear();
		window.display();
	}
}
