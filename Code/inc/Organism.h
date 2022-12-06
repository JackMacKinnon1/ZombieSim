#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include "GameSpecs.h"
#include "City.h"
#include <vector>


using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	int width;
	int height;
	bool moved{};
	City *city;
    char type;
    int recCount{1};

	enum { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };

public:
	Organism();
	Organism( City *city, int width, int height );
	virtual ~Organism();

	virtual void move() = 0;
	//virtual void spawn() = 0;
	//virtual int getSpecies() = 0; //this could also be coded concrete here
	//virtual void getPosition() = 0;

	void setPosition( int x, int y );
    int getX();
    int getY();
    void setMoved(bool moved);
    char getType();
//	void endTurn();
//	bool isTurn();
//
//	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
