//
// Created by Vyntax on 30/08/2026.
//
#pragma once
#ifndef ROCKETS_OBSTACLE_H
#define ROCKETS_OBSTACLE_H
#include <SFML/System/Vector2.hpp>

struct Obstacle {
    sf::Vector2f position;
    float width;
    float height;
    Obstacle(const sf::Vector2f &position, const float &width, const float &height) {
        this->position = position;
        this->width = width;
        this->height = height;
    }

    [[nodiscard]] bool contains(const sf::Vector2f &pos) const {
        return pos.x > position.x &&
            pos.x < position.x + width &&
            pos.y > position.y &&
            pos.y < position.y + height;
    }
};
#endif //ROCKETS_OBSTACLE_H