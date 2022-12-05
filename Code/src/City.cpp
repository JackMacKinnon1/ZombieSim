//
// Created by w0449149 on 2022-12-05.
//

#include "../inc/City.h"
#include "../inc/Human.h"
#include "../inc/Zombie.h"


City::City() :grid(){
    //make a for loop to fill the grid
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            //pick a random number to make a human or zombie or empty
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 2);
            int random = dis(gen);

            if (random == 0) {
                grid[i][j] = new Human(this, j, i);
            } else if (random == 1) {
                grid[i][j] = new Zombie(this, j, i);
            } else {
                grid[i][j] = nullptr;
            }
        }
    }
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
                    SetConsoleTextAttribute(hConsole, 10);
                } else if (j->getType() == ZOMBIE_CH) {
                    SetConsoleTextAttribute(hConsole, 12);
                }
                output << j->getType();
            } else {
                SetConsoleTextAttribute(hConsole, 7);
                output << '-';
            }
            output << ' ';
        }
        output << endl;
    }
    return output;
}
