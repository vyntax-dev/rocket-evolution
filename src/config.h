//
// Created by Vyntax on 26/08/2026.
//
#pragma once
#ifndef SFML_THING_CONFIG_H
#define SFML_THING_CONFIG_H
#endif //SFML_THING_CONFIG_H

namespace conf {
    // Window config
    constexpr sf::Vector2u windowSize = {1920, 1080};
    constexpr sf::Vector2f windowSizeF = static_cast<sf::Vector2f>(windowSize);
    constexpr uint32_t framerate = 60;
    constexpr float dt = 1.0 / static_cast<float>(framerate);
    constexpr sf::Color bgColor{2, 2, 10};

    // Rocket config
    constexpr uint32_t count = 5;
    constexpr float scale = 20.0f;
    constexpr float far = 10.0f;
    constexpr float near = 0.01f;
    constexpr float speed = 2.0f;
    constexpr int vertexCount = 3;
    constexpr sf::Color color{250,128,114};
}