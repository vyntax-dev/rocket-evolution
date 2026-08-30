//
// Created by Vyntax on 26/08/2026.
//

#include "events.h"
#include <iostream>

float processEvents(sf::Window &window) {
    while ( const std::optional event = window.pollEvent() )
    {
        if ( event->is<sf::Event::Closed>() )
            window.close();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        {
           return mouseWheelScrolled->delta;
        }
    }
    return 0;
}
