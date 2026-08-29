//
// Created by Vyntax on 28/08/2026.
//
#pragma once
#ifndef ROCKETS_ROCKET_H
#define ROCKETS_ROCKET_H

#include "genome.h"


struct Rocket {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float fitness;
    Genome genome;
    uint32_t geneCounter;

    explicit Rocket(const Genome &genome) : genome(genome) {
        this->genome = genome;
        position = conf::spawnOrigin;
        velocity = {0, 0};
        acceleration = {0, 0};
        fitness = 0;
        geneCounter = 0;
    }

    void applyForce(const sf::Vector2f &force) {
        acceleration += force;
    }

    void update() {
        velocity += acceleration;
        position += velocity;
        acceleration = {0, 0};
    }

    void run() {
        applyForce(genome.genes[geneCounter]);
        geneCounter++;
        update();
    }

    void calculateFitness(const sf::Vector2f &target) {
        const float dx = position.x - target.x;
        const float dy = position.y - target.y;
        const float distance = dx*dx + dy*dy;
        fitness = 1 / distance;
    }
};

struct Population {
    vector<Rocket> population;
    uint32_t generations;
    explicit Population() {
      generations = 1;
      population.reserve(conf::count);
      for (uint32_t i = 0; i < conf::count; i++) {
          population.emplace_back(Genome());
      }
    }

    void fitness(const sf::Vector2f &target) {
        for (auto &rocket : population) {
            rocket.calculateFitness(target);
        }
    }

    void selection() {
        float totalFitness = 0;
        for (const auto &rocket : population) {
            totalFitness += rocket.fitness;
        }
        for (auto &rocket : population) {
            rocket.fitness /= totalFitness;
        }
    }

    void breed() {
        // Weighted selection via discrete distribution
        static random_device rd;
        static mt19937 gen(rd());
        vector<float> weights;
        weights.reserve(conf::count);
        for (const Rocket& rocket : population) weights.push_back(rocket.fitness + 0.0001f);
        discrete_distribution<> distrib(weights.begin(), weights.end());

        // make the new population or smth
        vector<Rocket> newPopulation;
        newPopulation.reserve(conf::count);
        for (uint32_t i = 0; i < conf::count; i++) {
            const Rocket &parentA = population[distrib(gen)];
            const Rocket &parentB = population[distrib(gen)];

            Rocket child = Rocket(parentA.genome.breed(parentB.genome));
            child.genome.mutate();
            newPopulation.push_back(child);
        }
        population = std::move(newPopulation);
    }

    void live() {
        for (auto &rocket : population) {
            rocket.run();
        }
    }
};

#endif //ROCKETS_ROCKET_H