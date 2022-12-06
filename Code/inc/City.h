#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include <windows.h>
#include <random>
#include "GameSpecs.h"

using namespace std;

class Organism;

const int GRID_WIDTH = GRIDSIZE;
const int GRID_HEIGHT = GRIDSIZE;

class City
{
protected:
	Organism *grid[GRID_HEIGHT][GRID_WIDTH];
    int humanCount{};
    int zombieCount{};
    int generation{};
    bool diverse{true};
    int killCount{};


public:
	City();
	virtual ~City();

	Organism *getOrganism( int x, int y );
	void setOrganism( Organism *organism, int x, int y );

	void move();

	friend ostream& operator<<( ostream &output, City &city );

    int getHumanCount();
    int getZombieCount();
    int getGeneration();

    bool hasDiversity();

    void countOrganisms();
    void addKill();
    int getKillCount();
    void subKill();

};

#endif

