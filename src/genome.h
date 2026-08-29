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
    vector<sf::Vector2f> genes;
    float maxForce = conf::maxForce;

    explicit Genome() {
        genes.reserve(conf::lifespan);

        static random_device rd;
        static mt19937 gen(rd());
        uniform_real_distribution<> distrib(-1, 1);
        uniform_real_distribution<> distrib2(0, maxForce);
        for (int i = 0; i < conf::lifespan; i++) {
            genes.emplace_back(static_cast<float>(distrib(gen)),
                                static_cast<float>(distrib(gen)));
            genes[i] = genes[i].normalized();

            // multiply by random number up to max force
            genes[i] *= static_cast<float>(distrib2(gen));
        }
    }

    [[nodiscard]] Genome breed(const Genome &mate) const {
        Genome child;

        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, conf::lifespan - 1);
        const int until = distrib(gen);

        for (int i = 0; i < conf::lifespan; i++) {
            if (i < until) child.genes[i] = this->genes[i];
            else child.genes[i] = mate.genes[i];
        }
        return child;
    }

    void mutate() {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_real_distribution<> distrib(0, 1); // Mutation chance
        uniform_real_distribution<> distrib2(-1, 1); // Randomize gene
        uniform_real_distribution<> distrib3(0, maxForce); // Mult by up to max force

        for (int i = 0; i < conf::lifespan; i++) {
            if (distrib(gen) < conf::mutationRate) {
                genes[i] = sf::Vector2f{static_cast<float>(distrib2(gen)),
                                static_cast<float>(distrib2(gen))};
                genes[i] = genes[i].normalized();

                genes[i] *= static_cast<float>(distrib3(gen));
            }
        }
    }
};
#endif //ROCKETS_GENOME_H