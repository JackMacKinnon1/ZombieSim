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
    recCount++;
    starveCount++;

    //look around including diagonals for humans
    //if there are humans, pick a random one to move to
    //if there are no humans, move randomly
    std::vector<Organism*> humans;
    std::vector<std::vector<int>> cordsToMove;


    //check if move directions are off the grid, a human, a zombie, or an empty space

    //Looking north
    if (y - 1 >= 0) {
        //Check if north cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x, y - 1);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x, y - 1});
        }

    }
    //Looking south
    if (y + 1 < height) {
        //Check if south cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x, y + 1);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x, y + 1});
        }
    }
    //Looking west
    if (x - 1 >= 0) {
        //Check if west cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x - 1, y);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x - 1, y});
        }
    }
    //Looking east
    if (x + 1 < width) {
        //Check if east cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x + 1, y);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x + 1, y});
        }
    }
    //Looking north-west
    if (x - 1 >= 0 && y - 1 >= 0) {
        //Check if north-west cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x - 1, y - 1);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x - 1, y - 1});
        }
    }
    //Looking north-east
    if (x + 1 < width && y - 1 >= 0) {
        //Check if north-east cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x + 1, y - 1);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x + 1, y - 1});
        }
    }
    //Looking south-west
    if (x - 1 >= 0 && y + 1 < height) {
        //Check if south-west cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x - 1, y + 1);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x - 1, y + 1});
        }
    }
    //Looking south-east
    if (x + 1 < width && y + 1 < height) {
        //Check if south-east cell is zombie, human or empty
        Organism* tOrgan = city->getOrganism(x + 1, y + 1);

        if (tOrgan != nullptr) {
            if (tOrgan->getType() == HUMAN_CH) {
                humans.push_back(tOrgan);
            }
        } else {
            cordsToMove.push_back({x + 1, y + 1});
        }
    }

    //If there are humans, pick a random one to move to
    if (!humans.empty()) {
        //Generate a random number
        int randNum = rand() % humans.size();

        //Pick the human at the random number
        Organism* tOrgan = humans[randNum];

        //set the zombie to the human's location
        city->setOrganism(this, tOrgan->getX(), tOrgan->getY());

        //set the cell moved from to nullptr
        city->setOrganism(nullptr, x, y);

        //set the zombie's x and y to the human's x and y
        x = tOrgan->getX();
        y = tOrgan->getY();

        //Resetting the zombies eat count
        starveCount = 1;

        //delete the human
        delete tOrgan;
    }
    //If there are no humans, move randomly
    else if (!cordsToMove.empty()) {
        //Generate a random number for the cordsToMove vector
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, cordsToMove.size() - 1);
        int randNum = dis(gen);

        //Pick the cords at the random number
        std::vector<int> cords = cordsToMove[randNum];

        //set the zombie to the cords
        city->setOrganism(this, cords[0], cords[1]);

        //set the cell moved from to nullptr
        city->setOrganism(nullptr, x, y);

        //set the zombie's x and y to the cords
        x = cords[0];
        y = cords[1];
    }

    //Breed routine

    if (recCount == ZOMBIE_BREED) {

        std::vector<Organism*> convert;

        //Looking north
        if (y - 1 >= 0) {
            //Check if north cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x, y - 1);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking south
        if (y + 1 < height) {
            //Check if south cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x, y + 1);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking west
        if (x - 1 >= 0) {
            //Check if west cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x - 1, y);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking east
        if (x + 1 < width) {
            //Check if east cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x + 1, y);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking north-west
        if (x - 1 >= 0 && y - 1 >= 0) {
            //Check if north-west cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x - 1, y - 1);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking north-east
        if (x + 1 < width && y - 1 >= 0) {
            //Check if north-east cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x + 1, y - 1);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking south-west
        if (x - 1 >= 0 && y + 1 < height) {
            //Check if south-west cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x - 1, y + 1);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }
        //Looking south-east
        if (x + 1 < width && y + 1 < height) {
            //Check if south-east cell is zombie, human or empty
            Organism* tOrgan = city->getOrganism(x + 1, y + 1);

            if (tOrgan != nullptr) {
                if (tOrgan->getType() == HUMAN_CH) {
                    convert.push_back(tOrgan);
                }
            }
        }

        if (!convert.empty()) {
            //Generate a random number for the convert vector
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, convert.size() - 1);
            int randNum = dis(gen);

            //Pick the human at the random number
            Organism *tOrgan = convert[randNum];


            //Set location of the selected human to a new zombie
            city->setOrganism(new Zombie(city, tOrgan->getX(), tOrgan->getY()), tOrgan->getX(), tOrgan->getY());

            //Deleting the human
            delete tOrgan;

            //Resetting the breed count
            recCount = 1;
            city->addKill();

        }

    }

    //Starve routine

    if (starveCount == ZOMBIE_STARVE) {

        //Zombie has failed to eat a human and will convert itself into a human
        Organism *convertOrgan = city->getOrganism(x, y);

        //set this grid location to a new human
        city->setOrganism(new Human(city, x, y), x, y);
        //city->setOrganism(nullptr, x, y);
        //delete converted Organism
        city->subKill();

        delete convertOrgan;


    }

}


