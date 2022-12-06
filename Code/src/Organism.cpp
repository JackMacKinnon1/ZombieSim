//
// Created by w0449149 on 2022-12-05.
//

#include "../inc/Organism.h"

Organism::Organism() {
    type = ' ';
    city = nullptr;
    x = 0;
    y = 0;
    width = GRID_WIDTH;
    height = GRID_HEIGHT;
}

Organism::Organism(City *city, int width, int height) {
    this->type = ' ';
    this->city = city;
    this->width = GRID_WIDTH;
    this->height = GRID_HEIGHT;
    this->x = width;
    this->y = height;
}

Organism::~Organism() {
    city = nullptr;
}

void Organism::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

char Organism::getType() {
    return type;
}

void Organism::setMoved(bool moved) {
    this->moved = moved;
}

int Organism::getX() {
    return x;
}

int Organism::getY() {
    return y;
}
