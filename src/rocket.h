//
// Created by Vyntax on 28/08/2026.
//
#pragma once
#ifndef ROCKETS_ROCKET_H
#define ROCKETS_ROCKET_H

#include "SFML/System/Vector2.hpp"


struct Rocket {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float fitness;

    Rocket(const float &x, const float &y) {
        position = {x, y};
        velocity = {0, 0};
        acceleration = {0, 0};
        fitness = 0;
    }

    void applyForce(const sf::Vector2f &force) {
        acceleration += force;
    }

    void update() {
        velocity += acceleration;
        position += velocity;
        acceleration = {0, 0};
    }

    void calculateFitness(const float &targetX, const float &targetY) {
        const float dx = position.x - targetX;
        const float dy = position.y - targetY;
        fitness = sqrtf(dx * dx + dy * dy);
    }
};


#endif //ROCKETS_ROCKET_H