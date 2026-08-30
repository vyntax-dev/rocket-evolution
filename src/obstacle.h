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
    sf::Angle rotation = sf::degrees(0);

    Obstacle(const sf::Vector2f &position, const float &width, const float &height) {
        this->position = position;
        this->width = width;
        this->height = height;
    }

    [[nodiscard]] bool contains(const sf::Vector2f &pos) const {
        // Translate point relative to rectangle's center
        const sf::Vector2f rel = pos - position;

        // Rotate the point by the NEGATIVE of the rectangle's rotation
        // (equivalent to rotating our test point into the rectangle's local, un-rotated space)
        const float rad = -rotation.asRadians();
        const float c = std::cos(rad);
        const float s = std::sin(rad);
        const sf::Vector2f local{
            rel.x * c - rel.y * s,
            rel.x * s + rel.y * c
        };

        // Now test against an axis-aligned box centered at origin
        return local.x > -width / 2.f && local.x < width / 2.f &&
               local.y > -height / 2.f && local.y < height / 2.f;
    }
};
#endif //ROCKETS_OBSTACLE_H