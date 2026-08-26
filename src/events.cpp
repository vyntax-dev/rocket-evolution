//
// Created by Vyntax on 26/08/2026.
//

#include <SFML/Window.hpp>
#include "events.h"

void processEvents(sf::Window &window) {
    while ( const std::optional event = window.pollEvent() )
    {
        if ( event->is<sf::Event::Closed>() )
            window.close();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();
    }
}
