//
// Created by Vyntax on 28/08/2026.
//
#pragma once
#ifndef ROCKETS_ROCKET_H
#define ROCKETS_ROCKET_H

#include "SFML/System/Vector2.hpp"
#include "genome.h"


struct Rocket {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float fitness;
    Genome genome;
    uint32_t geneCounter;

    Rocket(const float &x, const float &y, const Genome &genome) : genome(genome) {
        this->genome = genome;
        position = {x, y};
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
    float mutationRate;
    vector<Rocket> population;
    uint32_t generations;
    explicit Population(const float &mutation) {
      mutationRate = mutation;
      generations = 0;
      population.reserve(conf::count);
      for (uint32_t i = 0; i < conf::count; i++) {
          population[i] = Rocket(320, 220, Genome(conf::lifespan));
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
        vector<Rocket> newPopulation;
        for (uint32_t i = 0; i < conf::count; i++) {
            //Rocket parentA = weighted selection()
        }
    }
};

#endif //ROCKETS_ROCKET_H