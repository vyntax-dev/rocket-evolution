//
// Created by Vyntax on 28/08/2026.
//
#pragma once
#ifndef ROCKETS_ROCKET_H
#define ROCKETS_ROCKET_H

#include "genome.h"
#include "obstacle.h"


struct Rocket {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float fitness;
    Genome genome;
    uint32_t geneCounter;
    bool hitObstacle;
    bool hitTarget;
    float recordDistance;
    uint32_t finishCounter;

    explicit Rocket(const Genome &genome) : genome(genome) {
        this->genome = genome;
        position = conf::spawnOrigin;
        velocity = {0, 0};
        acceleration = {0, 0};
        fitness = 0;
        geneCounter = 0;
        hitObstacle = false;
        hitTarget = false;
        recordDistance = 3e38f;
        finishCounter = 0;
    }

    void applyForce(const sf::Vector2f &force) {
        acceleration += force;
    }

    void update() {
        velocity += acceleration;
        position += velocity;
        acceleration = {0, 0};
    }

    void run(const Obstacle &obstacle, const Obstacle &target) {
        if (!hitObstacle && !hitTarget) {
            applyForce(genome.genes[geneCounter]);
            geneCounter++;
            update();

            checkObstacles(obstacle);
            checkTarget(target);
        }
    }

    void calculateFitness() {
        fitness = 1 / (static_cast<float>(finishCounter) * recordDistance);
        fitness = static_cast<float>(pow(fitness, 4));

        if (hitObstacle) fitness *= 0.1f;
        if (hitTarget) fitness *= 2.f;
    }

    void checkObstacles(const Obstacle &obstacle) {
        if (obstacle.contains(position)) {
            hitObstacle = true;
        }
    }

    void checkTarget(const Obstacle &target) {
        const float dx = position.x - target.position.x;
        const float dy = position.y - target.position.y;
        if (const float distance = sqrt(dx*dx + dy*dy); distance < recordDistance) {
            recordDistance = distance;
        }

        if (target.contains(position))
            hitTarget = true;
        else finishCounter++;
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

    void fitness() {
        for (auto &rocket : population) {
            rocket.calculateFitness();
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

    void live(const Obstacle &obstacle, const Obstacle &target) {
        for (auto &rocket : population) {
            rocket.run(obstacle, target);
        }
    }
};

#endif //ROCKETS_ROCKET_H