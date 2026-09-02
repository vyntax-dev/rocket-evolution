//
// Created by Vyntax on 26/08/2026.
//
#pragma once
#ifndef SFML_THING_CONFIG_H
#define SFML_THING_CONFIG_H
#include <fstream>
#include <string>

namespace conf {
    // Window config
    constexpr uint32_t framerate = 60;
    constexpr float dt = 1.0 / static_cast<float>(framerate);
    constexpr sf::Color bgColor{2, 2, 10};

    // Rocket config
    inline uint32_t count;
    inline uint32_t lifespan;
    inline float mutationRate;
    // Take the above 3 variables from the cfg file
    inline void read() {
        static std::ifstream configFile("res/settings.cfg");
        std::string line;

        while (std::getline(configFile, line)) {
            if (line[0] == '#' || line.empty()) continue;    // Skip comments & empty lines
            if (line[0] == 'c')                                         // Get count
                count = std::stoi(line.substr(line.find('=') + 1, line.size() - 1));

            else if (line[0] == 'm')                                // Get mutation rate
                mutationRate = std::stof(line.substr(line.find('=') + 1, line.size() - 1)) / 100.f;

            else if (line[0] == 'l')                                // Get lifespan
                lifespan = std::stoi(line.substr(line.find('=') + 1, line.size() - 1)) * framerate;
        }
    }

    constexpr float scale = 10.0f;
    constexpr float maxForce = 0.5f;
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

#endif //SFML_THING_CONFIG_H