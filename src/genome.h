//
// Created by Vyntax on 28/08/2026.
//
#pragma once
#ifndef ROCKETS_GENOME_H
#define ROCKETS_GENOME_H
#include <random>
#include <SFML/System/Vector2.hpp>
#include "config.h"

using namespace std;

struct Genome {
    std::vector<sf::Vector2f> genes;
    float maxForce = conf::maxForce;

    explicit Genome(const int &lifespan) {

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> distrib(-1, 1);
        std::uniform_real_distribution<> distrib2(0, maxForce);
        for (int i = 0; i < lifespan; i++) {
            genes[i] = {static_cast<float>(distrib(gen)),
                                static_cast<float>(distrib(gen))};
            genes[i] = genes[i].normalized();

            genes[i] *= static_cast<float>(distrib2(gen));
        }
    }
};
#endif //ROCKETS_GENOME_H