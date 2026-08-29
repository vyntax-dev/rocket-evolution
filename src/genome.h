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

    explicit Genome() {

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> distrib(-1, 1);
        std::uniform_real_distribution<> distrib2(0, maxForce);
        for (int i = 0; i < conf::lifespan; i++) {
            genes[i] = {static_cast<float>(distrib(gen)),
                                static_cast<float>(distrib(gen))};
            genes[i] = genes[i].normalized();

            // multiply by random number up to max force
            genes[i] *= static_cast<float>(distrib2(gen));
        }
    }

    [[nodiscard]] Genome breed(const Genome &mate) const {
        Genome child;

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 2);
        const int until = distrib(gen);

        for (int i = 0; i < 2; i++) {
            if (i < until) child.genes[i] = this->genes[i];
            else child.genes[i] = mate.genes[i];
        }
        return child;
    }
};
#endif //ROCKETS_GENOME_H