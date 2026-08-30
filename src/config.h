//
// Created by Vyntax on 26/08/2026.
//
#pragma once
#ifndef SFML_THING_CONFIG_H
#define SFML_THING_CONFIG_H
#endif //SFML_THING_CONFIG_H

namespace conf {
    // Window config
    constexpr uint32_t framerate = 60;
    constexpr float dt = 1.0 / static_cast<float>(framerate);
    constexpr sf::Color bgColor{2, 2, 10};

    // Rocket config
    constexpr uint32_t count = 100;
    constexpr uint32_t lifespan = 250;
    constexpr float scale = 20.0f;
    constexpr float maxForce = 0.3f;
    constexpr float mutationRate = 0.01f;
    constexpr int vertexCount = 3;
    constexpr sf::Color color{250,128,114, 50};
    constexpr sf::Vector2f spawnOrigin{320, 220};

    // Target config
    constexpr float targetWidth = 50.0f;
    constexpr float targetHeight = 50.0f;
    constexpr sf::Color targetColor{50,150,50};
    constexpr sf::Vector2f targetOrigin{600, 500};

    // Obstacle config
    constexpr float obstacleWidth = 300.0f;
    constexpr float obstacleHeight = 20.0f;
    constexpr sf::Color obstacleColor{50,50,50};
    constexpr sf::Vector2f obstacleOrigin{400,320};
}