//
// Created by Vyntax on 26/08/2026.
//

#ifndef SFML_THING_STAR_H
#define SFML_THING_STAR_H

#endif //SFML_THING_STAR_H
#pragma once
#include <SFML/System/Vector2.hpp>

struct Star {
    sf::Vector2f pos;
    mutable float z = 1.0f;
};