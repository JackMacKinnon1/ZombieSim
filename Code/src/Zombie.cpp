//
// Created by w0449149 on 2022-12-05.
//
#include "../inc/Zombie.h"

Zombie::Zombie() : Organism() {
    type = ZOMBIE_CH;
}

Zombie::Zombie(City *city, int width, int height) : Organism(city, width, height) {
    type = ZOMBIE_CH;
}

Zombie::~Zombie() = default;

void Zombie::move() {
    if (moved) return;
    moved = true;
}


