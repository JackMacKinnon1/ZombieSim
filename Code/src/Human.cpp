//
// Created by w0449149 on 2022-12-05.
//

#include "../inc/Human.h"

Human::Human() : Organism() {
    type = HUMAN_CH;
}

Human::Human(City *city, int width, int height) : Organism(city, width, height) {
    type = HUMAN_CH;
}

Human::~Human() = default;

void Human::move() {
    if (moved) return;
    moved = true;

    //pick a random direction to move to
    //check if adjacent space is empty or is off the grid
    std::vector<int> directions;

    //check if move directions are off the grid or occupied
    if (x - 1 >= 0 && city->getOrganism(x - 1, y) == nullptr) {
        directions.push_back(WEST);
    }
    if (x + 1 < width && city->getOrganism(x + 1, y) == nullptr) {
        directions.push_back(EAST);
    }
    if (y - 1 >= 0 && city->getOrganism(x, y - 1) == nullptr) {
        directions.push_back(NORTH);
    }
    if (y + 1 < height && city->getOrganism(x, y + 1) == nullptr) {
        directions.push_back(SOUTH);
    }

    //Pick a random direction to move to
    if (!directions.empty()) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, directions.size() - 1);
        int random = dis(gen);
        int direction = directions[random];

        //move to the new location
        if (direction == NORTH) {
            city->setOrganism(city->getOrganism(x, y), x, y - 1);
            city->setOrganism(nullptr, x, y);
            y--;
        } else if (direction == SOUTH) {
            city->setOrganism(city->getOrganism(x, y), x, y + 1);
            city->setOrganism(nullptr, x, y);
            y++;
        } else if (direction == WEST) {
            city->setOrganism(city->getOrganism(x, y), x - 1, y);
            city->setOrganism(nullptr, x, y);
            x--;
        } else if (direction == EAST) {
            city->setOrganism(city->getOrganism(x, y), x + 1, y);
            city->setOrganism(nullptr, x, y);
            x++;
        }
    }

    //increment the move count
    recCount++;

    //check if the human has moved 3 times
    if (recCount == 2) {
        //add valid directions to a vector
        std::vector<int> reproduce;
        if (x - 1 >= 0 && city->getOrganism(x - 1, y) == nullptr) {
            reproduce.push_back(WEST);
        }
        if (x + 1 < width && city->getOrganism(x + 1, y) == nullptr) {
            reproduce.push_back(EAST);
        }
        if (y - 1 >= 0 && city->getOrganism(x, y - 1) == nullptr) {
            reproduce.push_back(NORTH);
        }
        if (y + 1 < height && city->getOrganism(x, y + 1) == nullptr) {
            reproduce.push_back(SOUTH);
        }

        //pick a random direction to reproduce
        if (!reproduce.empty()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, reproduce.size() - 1);
            int random = dis(gen);
            int direction = reproduce[random];

            //reproduce in the new location
            if (direction == NORTH) {
                city->setOrganism(new Human(city, width, height), x, y - 1);
            } else if (direction == SOUTH) {
                city->setOrganism(new Human(city, width, height), x, y + 1);
            } else if (direction == WEST) {
                city->setOrganism(new Human(city, width, height), x - 1, y);
            } else if (direction == EAST) {
                city->setOrganism(new Human(city, width, height), x + 1, y);
            }
        }

        recCount = 0;
    }








}