//
// Created by w0449149 on 2022-12-05.
//

#include <algorithm>
#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"


City::City() :grid(){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, GRIDSIZE * GRIDSIZE);

    vector<int> humanPosition;
    vector<int> zombiePositions;

    //Random zombie and human position code credit to matt overflow

    for (int i = 0; i < ZOMBIE_STARTCOUNT; i++) {
        int random = dis(gen);

        if (count(zombiePositions.begin(), zombiePositions.end(), random)) {
            i--;
        } else {
            zombiePositions.push_back(random);
        }
    }

    for (int i = 0; i < HUMAN_STARTCOUNT; i++) {
        int random = dis(gen);

        if (count(humanPosition.begin(), humanPosition.end(), random) || count(zombiePositions.begin(), zombiePositions.end(), random)) {
            i--;
        } else {
            humanPosition.push_back(random);
        }

    }


    //make a for loop to fill the grid
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (count(zombiePositions.begin(), zombiePositions.end(), (i * GRIDSIZE) + j)) {
                this->grid[i][j] = new Zombie(this, j, i);
            }
            else if (count(humanPosition.begin(), humanPosition.end(), (i * GRIDSIZE) + j)) {
                this->grid[i][j] = new Human(this, j, i);
            }
            else {
                this->grid[i][j] = nullptr;
            }
        }
    }

    //Split the grid into 4 quadrants



}

City::~City() {
    for (auto & i : grid) {
        for (auto & j : i) {
            delete j;
        }
    }

}

Organism *City::getOrganism(int x, int y) {
    //check if the coordinates are valid
    if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
        return nullptr;
    }

    return grid[y][x];
}

void City::setOrganism(Organism *organism, int x, int y) {
    grid[y][x] = organism;
}

void City::move() {
    if (generation == ITERATIONS) {
        diverse = false;
    }

    generation++;
    for (auto & i : grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                j->move();
            }
        }
    }

    //reset moved flag
    for (auto & i : grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                j->setMoved(false);
            }
        }
    }
}

ostream &operator<<(ostream &output, City &city) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (auto & i : city.grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                //add color to the output
                if (j->getType() == HUMAN_CH) {
                    SetConsoleTextAttribute(hConsole, HUMAN_COLOR);
                } else if (j->getType() == ZOMBIE_CH) {
                    SetConsoleTextAttribute(hConsole, ZOMBIE_COLOR);
                }
                output << j->getType();
            } else {
                SetConsoleTextAttribute(hConsole, BLANK_COLOR);
                output << SPACE_CH;
            }
            output << "  ";
        }
        output << endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
    return output;
}

int City::getHumanCount(){
    return humanCount;
}

int City::getZombieCount(){
    return zombieCount;
}

void City::countOrganisms() {
    this->humanCount = 0;
    this->zombieCount = 0;
    for (auto & i : grid) {
        for (auto & j : i) {
            if (j != nullptr) {
                if (j->getType() == HUMAN_CH) {
                    this->humanCount++;
                } else if (j->getType() == ZOMBIE_CH) {
                    this->zombieCount++;
                }
            }
        }
    }

    if (humanCount == 0 || zombieCount == 0) {diverse = false;}
}

int City::getGeneration() {
    return generation;
}

bool City::hasDiversity() {
    return diverse;
}




